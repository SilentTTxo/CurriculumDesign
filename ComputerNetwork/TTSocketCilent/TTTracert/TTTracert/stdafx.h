// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

//IP报头
typedef struct
{
    unsigned char hdr_len:4;        //4位头部长度
    unsigned char version:4;        //4位版本号
    unsigned char tos;            //8位服务类型
    unsigned short total_len;        //16位总长度
    unsigned short identifier;        //16位标识符
    unsigned short frag_and_flags;    //3位标志加13位片偏移
    unsigned char ttl;            //8位生存时间
    unsigned char protocol;        //8位上层协议号
    unsigned short checksum;        //16位校验和
    unsigned long sourceIP;        //32位源IP地址
    unsigned long destIP;        //32位目的IP地址
} IP_HEADER;

//ICMP报头
typedef struct
{
    BYTE type;    //8位类型字段
    BYTE code;    //8位代码字段
    USHORT cksum;    //16位校验和
    USHORT id;    //16位标识符
    USHORT seq;    //16位序列号
} ICMP_HEADER;

//报文解码结构
typedef struct
{
    USHORT usSeqNo;        //序列号
    DWORD dwRoundTripTime;    //往返时间
    in_addr dwIPaddr;        //返回报文的IP地址
}DECODE_RESULT;

// TODO: 在此处引用程序需要的其他头文件
