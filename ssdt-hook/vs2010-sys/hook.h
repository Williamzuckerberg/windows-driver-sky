#ifndef HOOK_H
#define HOOK_H
#include "stdafx.h"


extern HANDLE thePid;
extern ULONG RealNtOpenAddress;
extern BOOLEAN is_hook;


typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase; //System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;
	//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase; //包含每个系统服务参数字节数表的基地址-系统服务参数表 
}*PServiceDescriptorTable; 

//取代系统的zwOpenprocess函数声明
extern "C" NTSTATUS __stdcall MyNtOpenProcess( 
	OUT     PHANDLE ProcessHandle, 
	IN     ACCESS_MASK DesiredAccess, 
	IN     POBJECT_ATTRIBUTES ObjectAttributes, 
	IN     PCLIENT_ID ClientId );

//系统的openprocess函数声明
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