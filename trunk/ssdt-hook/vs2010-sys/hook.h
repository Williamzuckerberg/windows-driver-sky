#ifndef HOOK_H
#define HOOK_H
#include "stdafx.h"


extern HANDLE thePid;
extern ULONG RealNtOpenAddress;
extern BOOLEAN is_hook;


typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase; //System Service Dispatch Table �Ļ���ַ  
	PVOID ServiceCounterTable;
	//������ SSDT ��ÿ�����񱻵��ô����ļ����������������һ����sysenter ���¡� 
	unsigned int NumberOfServices;//�� ServiceTableBase �����ķ������Ŀ��  
	PVOID ParamTableBase; //����ÿ��ϵͳ��������ֽ�����Ļ���ַ-ϵͳ��������� 
}*PServiceDescriptorTable; 

//ȡ��ϵͳ��zwOpenprocess��������
extern "C" NTSTATUS __stdcall MyNtOpenProcess( 
	OUT     PHANDLE ProcessHandle, 
	IN     ACCESS_MASK DesiredAccess, 
	IN     POBJECT_ATTRIBUTES ObjectAttributes, 
	IN     PCLIENT_ID ClientId );

//ϵͳ��openprocess��������
extern "C" typedef  NTSTATUS __stdcall NTOPENPROCESS 
	( 
	OUT PHANDLE ProcessHandle, 
	IN ACCESS_MASK AccessMask, 
	IN POBJECT_ATTRIBUTES ObjectAttributes, 
	IN PCLIENT_ID ClientId 
	);
extern NTOPENPROCESS   *  RealNtOpenProcess; 
extern PEPROCESS  EP;


void Hook();
void UnHook();


#endif