#include "SSDTWrite.h"

#pragma  INITCODE
JMPCODE oldCode;    //用来存放当前地址前5字节指令，用来还源curCode被修改后的值
PJMPCODE curCode;   //用来存放当前地址前5字节指令，用来被修改
BOOL isHOOK = false;
extern "C" int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
	ULONG cur_Addr,old_Addr;
	JMPCODE jmpCode;
	
    KdPrint(("Hello Driver World 驱动加载成功"));
	cur_Addr = asmReadSSDT();
	old_Addr = cReadSSDT();
	
	if (cur_Addr != old_Addr)
	{
		isHOOK = true;
		KdPrint(("Have be hooked!"));
		
	    //保存当前地址前5字节指今
		curCode = (PJMPCODE)cur_Addr;
		oldCode.E9 = curCode->E9;
		oldCode.JMPADDR = curCode->JMPADDR;
		
		//初始化跳转指令
		jmpCode.E9 = 0xE9;
		jmpCode.JMPADDR = cur_Addr - old_Addr - 5;
		
		__asm //去掉页面保护
		{
			cli
			mov eax,cr0
			and eax,not 10000h //and eax,0FFFEFFFFh
			mov cr0,eax

		}

		//用初始化的跳转指令修改当前地址的指令
		curCode->E9 = jmpCode.E9;
		curCode->JMPADDR = jmpCode.JMPADDR;
		
		
		__asm //恢复页保护
		 {
			mov eax,cr0
			or  eax,10000h //or eax,not 0FFFEFFFFh
			mov cr0,eax
			sti
		 }
		 
	}
	
	getSystemCallAddr();
	
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
	
	if (isHOOK)
	{
	__asm //去掉页面保护
		{
			cli
			mov eax,cr0
			and eax,not 10000h //and eax,0FFFEFFFFh
			mov cr0,eax
			
	int 3
		}
	
	//还原修改的指令
	curCode->E9 = oldCode.E9;
	curCode->JMPADDR = oldCode.JMPADDR;
		
	__asm //恢复页保护
		 {
			mov eax,cr0
			or  eax,10000h //or eax,not 0FFFEFFFFh
			mov cr0,eax
			sti
		 }
		}
		
	pDevObj = pDriverObject->DeviceObject;
	IoDeleteDevice(pDevObj);
	
	RtlInitUnicodeString(&symLinkName, L"\\??\\firstSysDevice");
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
	RtlInitUnicodeString(&symLinkName,L"\\??\\firstSysDevice");
	status = IoCreateSymbolicLink( &symLinkName,&devName );
	if (!NT_SUCCESS(status)) /*status等于0*/
	{
		IoDeleteDevice( pDevObj );
		return status;
	}
	return STATUS_SUCCESS;
}

//派遣函数
#pragma PAGECODE
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	)
{   
	ULONG info;
	
	NTSTATUS status = STATUS_SUCCESS;	
	//得到当前栈指针
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(pIrp);
	ULONG mf=stack->MajorFunction;//区分IRP
	switch (mf)
	{
	case IRP_MJ_DEVICE_CONTROL:
		{ 	KdPrint(("Enter myDriver_DeviceIOControl\n"));

		//得到输入缓冲区大小
		ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
		//得到输出缓冲区大小
		ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
		//得到IOCTL码
		ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;
		switch (code)
		{ 
		case add_code:
			{  		
				int a,b;
				KdPrint(("add_code 1111111111111111111\n"));
				//缓冲区方式IOCTL
				//获取缓冲区数据	a,b		
				int * InputBuffer = (int*)pIrp->AssociatedIrp.SystemBuffer;
				__asm
				{
					   mov eax,InputBuffer
						mov ebx,[eax]
						mov a,ebx
						mov ebx,[eax+4]
						mov b,ebx
				}
				KdPrint(("a=%d,b=%d \n", a,b));

				a=a+b;
				//C、驱动层返回数据至用户层
				//操作输出缓冲区
				//int* OutputBuffer = (int*)pIrp->AssociatedIrp.SystemBuffer;
				int OutputBuffer =(int)MmGetSystemAddressForMdlSafe(pIrp->MdlAddress,
					NormalPagePriority
					);
                KdPrint(("MmGetSystemAddressForMdlSafe=%x",OutputBuffer));
				__asm
				{
					    mov eax,a
						mov ebx,OutputBuffer
						mov [ebx],eax //bufferet=a+b

				}
				KdPrint(("a+b=%d \n",a));

				//设置实际操作输出缓冲区长度
				info = 4;
				break;
			}
		case sub_code:
			{
				break;
			}
		}//end code switch
		break;
		}
	case IRP_MJ_CREATE:
		{
			break;
		}
	case IRP_MJ_CLOSE:
		{
			break;
		}
	case IRP_MJ_READ:
		{
			break;
		}

	}

	//对相应的IPR进行处理
	pIrp->IoStatus.Information=info;//设置操作的字节数为0，这里无实际意义
	pIrp->IoStatus.Status=STATUS_SUCCESS;//返回成功
	IoCompleteRequest(pIrp,IO_NO_INCREMENT);//指示完成此IRP
	KdPrint(("离开派遣函数\n"));//调试信息
	return STATUS_SUCCESS; //返回成功
}

//读取SSDT
#pragma PAGECODE
ULONG asmReadSSDT()
{

	ULONG SSDT_NtOpenProcess_Cur_Addr;
__asm
{
	push eax
	push ebx
	mov eax,KeServiceDescriptorTable
	mov eax,[eax] //表的基地址
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
	//读取SSDT表中索引值为0x7A的函数
	//poi(poi(KeServiceDescriptorTable)+0x7a*4)
	t_addr=(LONG)KeServiceDescriptorTable->ServiceTableBase;
	KdPrint(("当前ServiceTableBase地址为%x \n",t_addr));
	SSDT_Adr=(PLONG)(t_addr+0x7A*4);
	KdPrint(("当前t_addr+0x7A*4=%x \n",SSDT_Adr)); 
	SSDT_NtOpenProcess_Cur_Addr=*SSDT_Adr;	
	KdPrint(("当前SSDT_NtOpenProcess_Cur_Addr地址为%x \n",SSDT_NtOpenProcess_Cur_Addr));
	
	return SSDT_NtOpenProcess_Cur_Addr;
}

ULONG getSystemCallAddr()
{
	UNICODE_STRING Old_NtOpenProcess;
    ULONG Old_Addr;
	RtlInitUnicodeString(&Old_NtOpenProcess,L"NtOpenProcess");
	Old_Addr=(ULONG)MmGetSystemRoutineAddress(&Old_NtOpenProcess);//取得NtOpenProcess的地址
	KdPrint(("取得原函数NtOpenProcess的值为 %x",Old_Addr));
	
	return Old_Addr;
}