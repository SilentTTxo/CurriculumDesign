// Ip3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Ip3.h"
#include "Ip3Dlg.h"

#include <winsock2.h>
#include<ws2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib, "ws2_32.lib ") 
#define MCASTADDR "233.0.0.101"//本例使用的多播组地址
#define MCASTPORT 8000  //本地端口号
#define BUFSIZE 1024//发送数据缓冲大小

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString Str;
SOCKET sock,sockM;
struct sockaddr_in local,remote,from;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
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
		   HWND hWnd = GetDlgItem(AfxGetMainWnd()->m_hWnd,IDC_EDIT1);
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

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIp3Dlg 对话框




CIp3Dlg::CIp3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIp3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIp3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIp3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &CIp3Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CIp3Dlg 消息处理程序

BOOL CIp3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	::AfxBeginThread(ThreadFun, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIp3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIp3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CIp3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIp3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
