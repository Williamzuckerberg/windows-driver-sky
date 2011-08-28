#include "stdafx.h"
#include "ctl_code.h"
#include "hook.h"
#include "Mem.h"

void SSDTHookUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS SSDTHookCreateClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS SSDTHookDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS SSDTHookDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

#ifdef __cplusplus
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath);
#endif

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING  RegistryPath)
{
	UNICODE_STRING DeviceName,Win32Device;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS status;
	unsigned i;

        //test memory
        memtest();

	RtlInitUnicodeString(&DeviceName,L"\\Device\\SSDTHook0");
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\SSDTHook0");

	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		DriverObject->MajorFunction[i] = SSDTHookDefaultHandler;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = SSDTHookCreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = SSDTHookCreateClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = SSDTHookDeviceControl;
	
	DriverObject->DriverUnload = SSDTHookUnload;
	status = IoCreateDevice(DriverObject,
							0,
							&DeviceName,
							FILE_DEVICE_UNKNOWN,
							0,
							FALSE,
							&DeviceObject);
	if (!NT_SUCCESS(status))
		return status;
	if (!DeviceObject)
		return STATUS_UNEXPECTED_IO_ERROR;

	DeviceObject->Flags |= DO_DIRECT_IO;
	DeviceObject->AlignmentRequirement = FILE_WORD_ALIGNMENT;
	status = IoCreateSymbolicLink(&Win32Device, &DeviceName);

	DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

void SSDTHookUnload(IN PDRIVER_OBJECT DriverObject)
{
	if (is_hook)
	{
		UnHook();
	}
	UNICODE_STRING Win32Device;
	RtlInitUnicodeString(&Win32Device,L"\\DosDevices\\SSDTHook0");
	IoDeleteSymbolicLink(&Win32Device);
	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS SSDTHookCreateClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS SSDTHookDefaultHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Irp->IoStatus.Status;
}

NTSTATUS SSDTHookDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	ULONG info;
	//得到当前栈指针
	KdPrint(("get commond form application"));
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG mf=stack->MajorFunction;//区分IRP
	if (mf == IRP_MJ_DEVICE_CONTROL)
	{
		//得到输入缓冲区大小
		ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
		//得到输出缓冲区大小
		ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
		//得到IOCTL码
		ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;
		switch (code)
		{
		case hook_code:
			{
				//获取缓冲区数据	a,b		
				int * InputBuffer = (int*)Irp->AssociatedIrp.SystemBuffer;
				_asm
				{
					mov eax,InputBuffer
					mov ebx,[eax]
					mov thePid,ebx

				}
				KdPrint(("设定被保护进程 MyPID=%d \n",(int)thePid));
				int* OutputBuffer = (int*)Irp->AssociatedIrp.SystemBuffer;
				_asm
				{
					mov eax,1
					mov ebx,OutputBuffer
					mov [ebx],eax //

				}
				info = 4;
			    Hook();
			}
			break;
		case unhook_code:
			{
				UnHook();
			}
			break;
		}
	}

	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Irp->IoStatus.Status;
}