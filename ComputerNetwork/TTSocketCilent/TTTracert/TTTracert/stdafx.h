// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

//IP��ͷ
typedef struct
{
    unsigned char hdr_len:4;        //4λͷ������
    unsigned char version:4;        //4λ�汾��
    unsigned char tos;            //8λ��������
    unsigned short total_len;        //16λ�ܳ���
    unsigned short identifier;        //16λ��ʶ��
    unsigned short frag_and_flags;    //3λ��־��13λƬƫ��
    unsigned char ttl;            //8λ����ʱ��
    unsigned char protocol;        //8λ�ϲ�Э���
    unsigned short checksum;        //16λУ���
    unsigned long sourceIP;        //32λԴIP��ַ
    unsigned long destIP;        //32λĿ��IP��ַ
} IP_HEADER;

//ICMP��ͷ
typedef struct
{
    BYTE type;    //8λ�����ֶ�
    BYTE code;    //8λ�����ֶ�
    USHORT cksum;    //16λУ���
    USHORT id;    //16λ��ʶ��
    USHORT seq;    //16λ���к�
} ICMP_HEADER;

//���Ľ���ṹ
typedef struct
{
    USHORT usSeqNo;        //���к�
    DWORD dwRoundTripTime;    //����ʱ��
    in_addr dwIPaddr;        //���ر��ĵ�IP��ַ
}DECODE_RESULT;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
