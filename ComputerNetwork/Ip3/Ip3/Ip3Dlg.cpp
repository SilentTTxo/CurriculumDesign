// Ip3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ip3.h"
#include "Ip3Dlg.h"

#include <winsock2.h>
#include<ws2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib, "ws2_32.lib ") 
#define MCASTADDR "233.0.0.101"//����ʹ�õĶಥ���ַ
#define MCASTPORT 8000  //���ض˿ں�
#define BUFSIZE 1024//�������ݻ����С

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString Str;
SOCKET sock,sockM;
struct sockaddr_in local,remote,from;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
UINT ThreadFun(LPVOID pParam){  //�߳�Ҫ���õĺ���
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
   //��sock�󶨵������˿���
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
   //����ಥ��

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
   //���նಥ���ݣ����յ�������ΪQUITʱ�˳�

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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CIp3Dlg �Ի���




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


// CIp3Dlg ��Ϣ�������

BOOL CIp3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	::AfxBeginThread(ThreadFun, this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIp3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CIp3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIp3Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
