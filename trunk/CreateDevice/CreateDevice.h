#include <ntddk.h>

#define INITCODE code_seg("INIT")
#define PAGECODE code_seg("PAGE")

#pragma INITCODE
VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateTheDevice(IN PDRIVER_OBJECT pDeviceObject);
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	);//ÅÉÇ²º¯Êý