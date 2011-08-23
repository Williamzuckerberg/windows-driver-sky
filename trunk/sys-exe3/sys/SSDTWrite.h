#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#include <NTDDK.h> //这里包含需要用C方式编译的头文件
#ifdef __cplusplus
}
#endif 
#include <windef.h>
#include "ctl_code.h"

#define INITCODE code_seg("INIT")
#define PAGECODE code_seg("PAGE")

typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase; //System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;
	//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase; //包含每个系统服务参数字节数表的基地址-系统服务参数表 
}*PServiceDescriptorTable;  
extern "C" extern PServiceDescriptorTable KeServiceDescriptorTable;

#pragma pack(1)
typedef struct _JMPCODE
{
	BYTE E9;
	ULONG JMPADDR;//88881234=B
}JMPCODE,*PJMPCODE;
#pragma pack()

#pragma PAGECODE
VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateTheDevice(IN PDRIVER_OBJECT pDeviceObject);
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	);//派遣函数

//读取当前SSDT中函数的地址
ULONG asmReadSSDT();
ULONG cReadSSDT();

//读取系统中函数的地址
ULONG getSystemCallAddr();