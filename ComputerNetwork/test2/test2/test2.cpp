// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"




int main(int argc,char **argv)

{
   WSADATA wsd;
   struct sockaddr_in local,remote,from;
   SOCKET sock,sockM;
   TCHAR recvbuf[BUFSIZE];

   int len=sizeof(struct sockaddr_in);
   int ret;

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
/*
   mcast.imr_multiaddr.s_addr=inet_addr(MCASTADDR);
   mcast.imr_interface.s_addr=INADDR_ANY;
   if(setsockopt(sockM,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mcast,
	   sizeof(mcast))==SOCKET_ERROR)
   {
	   printf("setsockopt(IP_ADD_MEMBERSHIP)failed:%d\n",WSAGetLastError());
	   closesocket(sockM);
	   WSACleanup;
	   return -1;
   
   
   }
*/
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
		   printf("recvfrom failed with :%d\n",WSAGetLastError());
		   closesocket(sockM);
		   closesocket(sock);
		   WSACleanup();
		   return -1;
	   
	   
	   }

	   if(strcmp(recvbuf,"QUIT")==0)  break;
	   else{
		   recvbuf[ret]='\0';
	       printf("RECV:'%s'FROM<%s>\n",recvbuf,inet_ntoa(from.sin_addr));
	   
	   }
   }

      closesocket(sockM);
   closesocket(sock);
   WSACleanup();
   return 0;
}

