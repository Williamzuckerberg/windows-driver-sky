#include "SSDTRead.h"

int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
    KdPrint(("Hello Driver World �������سɹ�"));
	
	asmReadSSDT();
	cReadSSDT();
	
	getSystemCallAddr();
	
	 //ע����ǲ����
	pDriverObject->MajorFunction[IRP_MJ_CREATE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE���IRP������
	pDriverObject->MajorFunction[IRP_MJ_CLOSE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE���IRP������
	pDriverObject->MajorFunction[IRP_MJ_READ]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE���IRP������
	pDriverObject->MajorFunction[IRP_MJ_CLOSE]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE���IRP������
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=ddk_DispatchRoutine_CONTROL; //IRP_MJ_CREATE���IRP������
	
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
	
    KdPrint(("Hello Driver World ����ж�سɹ�"));
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
			KdPrint(("��Դ����"));
		}
		
		if (STATUS_OBJECT_NAME_EXISTS == status)
		{
			KdPrint(("ָ������������"));
		}
		
		if (STATUS_OBJECT_NAME_COLLISION == status)
		{
			KdPrint(("//�������г�ͻ"));
		}
        
		KdPrint(("�豸����ʧ��"));
		return status;
	}
	
	KdPrint(("�����豸�ɹ�"));
	
	pDevObj->Flags |= DO_BUFFERED_IO;
	
	//������������
	RtlInitUnicodeString(&symLinkName,L"\\??\\firstSymDevice");
	status = IoCreateSymbolicLink( &symLinkName,&devName );
	if (!NT_SUCCESS(status)) /*status����0*/
	{
		IoDeleteDevice( pDevObj );
		return status;
	}
	return STATUS_SUCCESS;
}

//��ǲ����
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	)
{
	//����Ӧ��IPR���д���
	pIrp->IoStatus.Information=0;//���ò������ֽ���Ϊ0��������ʵ������
	pIrp->IoStatus.Status=STATUS_SUCCESS;//���سɹ�
	IoCompleteRequest(pIrp,IO_NO_INCREMENT);//ָʾ��ɴ�IRP
	KdPrint(("�뿪��ǲ����\n"));//������Ϣ
	return STATUS_SUCCESS; //���سɹ�
}

//��ȡSSDT
#pragma PAGECODE
ULONG asmReadSSDT()
{

	ULONG SSDT_NtOpenProcess_Cur_Addr;
__asm
{
	push eax
	push ebx
	mov eax,KeServiceDescriptorTable
	mov eax,[eax] //��Ļ���ַ
	//[[KeServiceDescriptorTable]+0x7A*4]
	mov ebx, 0x7A
	shl ebx, 2
	add eax, ebx
	mov eax, [eax]
	mov SSDT_NtOpenProcess_Cur_Addr, eax
	pop ebx
	pop eax
}
	KdPrint(("NtOpenProcess Current address is:%x", SSDT_NtOpenProcess_Cur_Addr));
	
	return SSDT_NtOpenProcess_Cur_Addr;
}

ULONG cReadSSDT()
{
	LONG *SSDT_Adr,SSDT_NtOpenProcess_Cur_Addr,t_addr; 
	//��ȡSSDT��������ֵΪ0x7A�ĺ���
	//poi(poi(KeServiceDescriptorTable)+0x7a*4)
	t_addr=(LONG)KeServiceDescriptorTable->ServiceTableBase;
	KdPrint(("��ǰServiceTableBase��ַΪ%x \n",t_addr));
	SSDT_Adr=(PLONG)(t_addr+0x7A*4);
	KdPrint(("��ǰt_addr+0x7A*4=%x \n",SSDT_Adr)); 
	SSDT_NtOpenProcess_Cur_Addr=*SSDT_Adr;	
	KdPrint(("��ǰSSDT_NtOpenProcess_Cur_Addr��ַΪ%x \n",SSDT_NtOpenProcess_Cur_Addr));
	
	return SSDT_NtOpenProcess_Cur_Addr;
}

ULONG getSystemCallAddr()
{
	UNICODE_STRING Old_NtOpenProcess;
    ULONG Old_Addr;
	RtlInitUnicodeString(&Old_NtOpenProcess,L"NtOpenProcess");
	Old_Addr=(ULONG)MmGetSystemRoutineAddress(&Old_NtOpenProcess);//ȡ��NtOpenProcess�ĵ�ַ
	KdPrint(("ȡ��ԭ����NtOpenProcess��ֵΪ %x",Old_Addr));
	
	return Old_Addr;
}