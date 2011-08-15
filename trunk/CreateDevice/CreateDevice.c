#include "CreateDevice.h"

int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
    KdPrint(("Hello Driver World 驱动加载成功"));
	
	 //注册派遣函数
	pDriverObject->MajorFunction[IRP_MJ_CREATE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE相关IRP处理函数
	pDriverObject->MajorFunction[IRP_MJ_CLOSE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE相关IRP处理函数
	pDriverObject->MajorFunction[IRP_MJ_READ]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE相关IRP处理函数
	pDriverObject->MajorFunction[IRP_MJ_CLOSE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE相关IRP处理函数
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE相关IRP处理函数
	
	CreateTheDevice(pDriverObject);
    pDriverObject->DriverUnload = Driver_Unload;
    return (1);
}

VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject)
{
	PDEVICE_OBJECT pDevObj;
	UNICODE_STRING symLinkName;
	
	pDevObj = pDriverObject->DeviceObject;
	IoDeleteDevice(pDevObj);
	
	RtlInitUnicodeString(&symLinkName, L"\\??\\firstSymDevice");
	IoDeleteSymbolicLink(&symLinkName);
	
    KdPrint(("Hello Driver World 驱动卸载成功"));
}

NTSTATUS CreateTheDevice(IN PDRIVER_OBJECT pDeviceObject)
{
	NTSTATUS status;
	PDEVICE_OBJECT pDevObj;
	
	UNICODE_STRING devName;
	UNICODE_STRING symLinkName;
	
	RtlInitUnicodeString(&devName, L"\\Device\\first_Device");
	
	//create device
	status = IoCreateDevice(pDeviceObject,\
		0,\
		&devName,\
		FILE_DEVICE_UNKNOWN,\
		0,\
		TRUE,\
		&pDevObj\
	);
	if (!NT_SUCCESS(status))
	{
		if (STATUS_INSUFFICIENT_RESOURCES == status)
		{
			KdPrint(("资源不足"));
		}
		
		if (STATUS_OBJECT_NAME_EXISTS == status)
		{
			KdPrint(("指定对象名存在"));
		}
		
		if (STATUS_OBJECT_NAME_COLLISION == status)
		{
			KdPrint(("//对象名有冲突"));
		}
        
		KdPrint(("设备创建失败"));
		return status;
	}
	
	KdPrint(("创建设备成功"));
	
	pDevObj->Flags |= DO_BUFFERED_IO;
	
	//创建符号链接
	RtlInitUnicodeString(&symLinkName,L"\\??\\firstSymDevice");
	status = IoCreateSymbolicLink( &symLinkName,&devName );
	if (!NT_SUCCESS(status)) /*status等于0*/
	{
		IoDeleteDevice( pDevObj );
		return status;
	}
	return STATUS_SUCCESS;
}

//派遣函数
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	)
{
	//对相应的IPR进行处理
	pIrp->IoStatus.Information=0;//设置操作的字节数为0，这里无实际意义
	pIrp->IoStatus.Status=STATUS_SUCCESS;//返回成功
	IoCompleteRequest(pIrp,IO_NO_INCREMENT);//指示完成此IRP
	KdPrint(("离开派遣函数\n"));//调试信息
	return STATUS_SUCCESS; //返回成功
}