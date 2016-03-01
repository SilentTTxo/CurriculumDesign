// m3Dlg.cpp : implementation file
//
#include "stdafx.h"
#include <winsock2.h>
#include "m3.h"
#include "m3Dlg.h"
#include<ws2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib, "ws2_32.lib ") 
#define MCASTADDR "233.0.0.2"//本例使用的多播组地址
#define MCASTPORT 7119  //本地端口号
#define BUFSIZE 1024//发送数据缓冲大小
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CString Str;
SOCKET sock,sockM;
struct sockaddr_in local,remote,from;
UINT ThreadFun(LPVOID pParam){  //线程要调用的函数
   WSADATA wsd;
   int len=sizeof(struct sockaddr_in);
   int ret;
	TCHAR recvbuf[BUFSIZE];
   if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
   {
	   printf("WSAStartup()failed\n");
	   return -1;
   }
   if((sock=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,
	   WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF|
	   WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
   {
	   printf("socket failed with :%d\n",WSAGetLastError());
	   WSACleanup();
	   return -1;
   }
   //将sock绑定到本机端口上
   local.sin_family=AF_INET;
   local.sin_port=htons(MCASTPORT);
   local.sin_addr.s_addr=INADDR_ANY;

   if(bind(sock,(struct sockaddr*)&local,sizeof(local))==SOCKET_ERROR)
   {
	   printf("bind failed with %d\n",WSAGetLastError());
	   closesocket(sock);
	   WSACleanup();
	   return -1;
   
   
   }
   //加入多播组

   remote.sin_family=AF_INET;
   remote.sin_port=htons(MCASTPORT);
   remote.sin_addr.s_addr=inet_addr(MCASTADDR);

   if((sockM=WSAJoinLeaf(sock,(SOCKADDR*)&remote,sizeof(remote),
	   NULL,NULL,NULL,NULL,
	   JL_BOTH))==INVALID_SOCKET)
   {
     printf("WSAJoinLeaf()failed:%d\n",WSAGetLastError());
     closesocket(sock);
	 WSACleanup();
	 return -1;
   }
   //接收多播数据，当收到的数据为QUIT时退出

   while(1)
   {
	   if((ret=recvfrom(sock,recvbuf,BUFSIZE,0,
		   (struct sockaddr*)&from,&len))==SOCKET_ERROR)
	   {
		   //printf("recvfrom failed with :%d\n",WSAGetLastError());
		   closesocket(sockM);
		   closesocket(sock);
		   WSACleanup();
		   return -1;
	   }
	   if(strcmp(recvbuf,"QUIT")==0)  break;
	   else{
		   recvbuf[ret]='\0';
		   Str+=inet_ntoa(from.sin_addr);
		   Str+=":";
		   Str+=recvbuf;
		   Str+="\r\n";
		   HWND hWnd = GetDlgItem(AfxGetMainWnd()->m_hWnd,TextView);
		   CWnd *pWnd = CWnd::FromHandle(hWnd);
		   pWnd->SetWindowText(_T(Str));

	   }
   }

   closesocket(sockM);
   closesocket(sock);
   WSACleanup();
   return 0;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CM3Dlg dialog

CM3Dlg::CM3Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CM3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CM3Dlg)
	m_content = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CM3Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_content);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CM3Dlg, CDialog)
//{{AFX_MSG_MAP(CM3Dlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(send, Onsend)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CM3Dlg message handlers

BOOL CM3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	::AfxBeginThread(ThreadFun, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CM3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CM3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CM3Dlg::Onsend() 
{
		UpdateData(TRUE);
		if(sendto(sockM,m_content,m_content.GetLength(),0,(struct sockaddr*)&remote,sizeof(remote))==SOCKET_ERROR)
		{
			AfxMessageBox("sendto faild with:");
			closesocket(sockM);
			closesocket(sock);
			WSACleanup();
		} 
        /*
		AfxMessageBox("SUCCESS");
		Str+="自己:";
		Str+=m_content;
		Str+="\r\n";
		GetDlgItem(TextView)->SetWindowText(_T(Str));*/
}
