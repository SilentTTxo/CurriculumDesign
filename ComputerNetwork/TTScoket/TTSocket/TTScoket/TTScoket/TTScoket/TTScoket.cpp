// TTScoket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

SOCKET serConn;

DWORD WINAPI funproc(LPVOID lpparentet)  
{  
	while(1){
		Sleep(100);
		char receiveBuf[100];//����
		memset(receiveBuf, 0, 100);
		if(recv(serConn,receiveBuf,100,0)!=-1){
			printf("�ͻ��ˣ�%s\n",receiveBuf);
		}
	}
    return 0;  
}  
int main()
{
	//�����׽���
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest=MAKEWORD(1,1);
	int err;
	err=WSAStartup(myVersionRequest,&wsaData);
	if (!err)
	{
		printf("����˾���\n");
	} 
	else
	{
		//��һ�����׽���
		printf("Scoketδ��!");
		return -1;
	}
	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���
	//��Ҫ�󶨵Ĳ���
	SOCKADDR_IN addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//ip��ַ
	addr.sin_port=htons(6000);//�󶨶˿�

	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//�����
	listen(serSocket,5);//���еڶ������������ܹ����յ�����������

	//////////////////////////////////////////////////////////////////////////
	//��ʼ���м���
	//////////////////////////////////////////////////////////////////////////
	SOCKADDR_IN clientsocket;
	int len=sizeof(SOCKADDR);
	serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���
	CreateThread(NULL,0,funproc,NULL,0,NULL);
	while (1)
	{
		char sendBuf[100];
		gets(sendBuf);
		//sprintf(sendBuf,"welcome %s to bejing",inet_ntoa(clientsocket.sin_addr));//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������
		send(serConn,sendBuf,strlen(sendBuf)+1,0);
	}
	closesocket(serConn);//�ر�
		WSACleanup();//�ͷ���Դ�Ĳ���
}

