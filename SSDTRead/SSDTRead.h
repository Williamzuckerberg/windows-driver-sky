#include <ntddk.h>

#define INITCODE code_seg("INIT")
#define PAGECODE code_seg("PAGE")

typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase; //System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;
	//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase; //包含每个系统服务参数字节数表的基地址-系统服务参数表 
}*PServiceDescriptorTable;  
extern PServiceDescriptorTable KeServiceDescriptorTable;

#pragma INITCODE
VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateTheDevice(IN PDRIVER_OBJECT pDeviceObject);
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	);//派遣函数

//读取当前SSDT中函数的地址
VOID asmReadSSDT();
VOID cReadSSDT();

//读取系统中函数的地址
VOID getSystemCallAddr();