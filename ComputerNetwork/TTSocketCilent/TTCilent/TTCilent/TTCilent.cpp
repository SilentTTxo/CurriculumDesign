// TTCilent.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
SOCKET clientSocket;

DWORD WINAPI funproc(LPVOID lpparentet)  
{  
	while(1){
		Sleep(100);
		char receiveBuf[100];
		memset(receiveBuf, 0, 100);
		if(recv(clientSocket,receiveBuf,100,0)!=-1){
			printf("����ˣ�%s\n",receiveBuf);
		}
	}
    return 0;  
}  
int main()
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//Э���İ汾��Ϣ
	if (!err)
	{
		printf("�ͻ��˾���!\n");
	}
	else
	{
		printf("�ͻ��˵�Ƕ���ִ�ʧ��!\n");
		return -1;//����
	}
	clientSocket=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	clientsock_in.sin_family=AF_INET;
	clientsock_in.sin_port=htons(6000);
	//bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//ע�����������
	//listen(clientSocket,5);
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//��ʼ����
	CreateThread(NULL,0,funproc,NULL,0,NULL);
	while(1){
		char str[100];
		gets(str);
		int sum = strlen(str)+1;
		send(clientSocket,str,strlen(str)+1,0);
	}
	closesocket(clientSocket);
	WSACleanup();
}

