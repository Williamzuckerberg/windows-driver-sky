#include "SSDTWrite.h"

#pragma  INITCODE
JMPCODE oldCode;    //������ŵ�ǰ��ַǰ5�ֽ�ָ�������ԴcurCode���޸ĺ��ֵ
PJMPCODE curCode;   //������ŵ�ǰ��ַǰ5�ֽ�ָ��������޸�
int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
	ULONG cur_Addr,old_Addr;
	JMPCODE jmpCode;
	
    KdPrint(("Hello Driver World �������سɹ�"));
	cur_Addr = asmReadSSDT();
	old_Addr = cReadSSDT();
	
	if (cur_Addr != old_Addr)
	{
		KdPrint(("Have be hooked!"));
		
	    //���浱ǰ��ַǰ5�ֽ�ָ��
		curCode = (PJMPCODE)cur_Addr;
		oldCode.E9 = curCode->E9;
		oldCode.JMPADDR = curCode->JMPADDR;
		
		//��ʼ����תָ��
		jmpCode.E9 = 0xE9;
		jmpCode.JMPADDR = cur_Addr - old_Addr - 5;
		
		__asm //ȥ��ҳ�汣��
		{
			cli
			mov eax,cr0
			and eax,not 10000h //and eax,0FFFEFFFFh
			mov cr0,eax

		}

		//�ó�ʼ������תָ���޸ĵ�ǰ��ַ��ָ��
		curCode->E9 = jmpCode.E9;
		curCode->JMPADDR = jmpCode.JMPADDR;
		
		
		__asm //�ָ�ҳ����
		 {
			mov eax,cr0
			or  eax,10000h //or eax,not 0FFFEFFFFh
			mov cr0,eax
			sti
		 }
	}
	
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
	
	__asm //ȥ��ҳ�汣��
		{
			cli
			mov eax,cr0
			and eax,not 10000h //and eax,0FFFEFFFFh
			mov cr0,eax

		}
	
	//��ԭ�޸ĵ�ָ��
	curCode->E9 = oldCode.E9;
	curCode->JMPADDR = oldCode.JMPADDR;
		
	__asm //�ָ�ҳ����
		 {
			mov eax,cr0
			or  eax,10000h //or eax,not 0FFFEFFFFh
			mov cr0,eax
			sti
		 }
		
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