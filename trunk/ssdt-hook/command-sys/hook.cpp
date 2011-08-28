#include "hook.h"

HANDLE thePid;
ULONG RealNtOpenAddress;
BOOLEAN is_hook = FALSE;

NTOPENPROCESS   *  RealNtOpenProcess; 
PEPROCESS  EP;
 
extern "C" extern PServiceDescriptorTable KeServiceDescriptorTable;

NTSTATUS __stdcall MyNtOpenProcess( 
	OUT     PHANDLE ProcessHandle, 
	IN     ACCESS_MASK DesiredAccess, 
	IN     POBJECT_ATTRIBUTES ObjectAttributes, 
	IN     PCLIENT_ID ClientId ) 
{ 
	NTSTATUS     rc; 
	HANDLE       PID; 

	KdPrint(("++++++++++++Entry MyNtOpenProcess int   ++++++++++++++\n"));  

	rc = (NTSTATUS)RealNtOpenProcess( ProcessHandle, DesiredAccess, ObjectAttributes, ClientId ); 	

	if( (ClientId != NULL) ) 
	{ 
		PID = ClientId->UniqueProcess; 	 
		KdPrint(( "------------------------- PID=%d--------------\n",(int*)PID ));

		// ����Ǳ�������PID����ܾ����ʣ������������Ϊ�� 
		if(PID == thePid) 
		{ 
			KdPrint(("���������� MyPID=%d \n",(int)thePid));
			//������� ����C���Ե� Printf
			ProcessHandle = NULL; //����ǹؼ�
			rc = STATUS_ACCESS_DENIED; //�������ֵ 
			//PsLookupProcessByProcessId((ULONG)PID,&EP);
			EP=PsGetCurrentProcess();			 
			KdPrint((" ACESS Process Name  --:%s--   \n",(PTSTR)((ULONG)EP+0x174)));

		} 
	} 

	return rc; 
} 

void Hook()
{
	is_hook=true;//���ñ�HOOK��־
	KdPrint(("++++HOOK START ++++-\n"));
	LONG *SSDT_Adr,SSDT_NtOpenProcess_Cur_Addr,t_addr; 

	KdPrint(("�����ɹ���������.............................\n"));
	//��ȡSSDT��������ֵΪ0x7A�ĺ���
	//poi(poi(KeServiceDescriptorTable)+0x7a*4)
	t_addr=(LONG)KeServiceDescriptorTable->ServiceTableBase;
	SSDT_Adr=(PLONG)(t_addr+0x7A*4);

	SSDT_NtOpenProcess_Cur_Addr=*SSDT_Adr;	 
	RealNtOpenAddress = *SSDT_Adr; 
	RealNtOpenProcess = ( NTOPENPROCESS *)RealNtOpenAddress; 

	KdPrint(( "��ʵ��NtOpenProcess��ַ: %x\n",(int) RealNtOpenAddress )); 
	KdPrint((" α��NTOpenProcess��ַ: %x\n", (int)MyNtOpenProcess ));  


	__asm //ȥ��ҳ�汣��
	{
		cli
			mov eax,cr0
			and eax,not 10000h //and eax,0FFFEFFFFh
			mov cr0,eax

	}


	*SSDT_Adr= (ULONG)MyNtOpenProcess; //SSDT HOOK


	__asm 
	{ 
		mov     eax, cr0 
			or     eax, 10000h 
			mov     cr0, eax 
			sti 
	}   
	return;
}

void UnHook()
{
	ULONG Old_ssdt; 
	Old_ssdt = (ULONG)KeServiceDescriptorTable->ServiceTableBase + 0x7A * 4; 
	if    (is_hook)
	{    
		is_hook=false;
		__asm 
		{ 
			cli 
				mov     eax, cr0 
				and     eax, not 10000h 
				mov     cr0, eax 
		} 

		// ��ԭSSDT 
		*((ULONG*)Old_ssdt) = (ULONG)RealNtOpenAddress; 

		__asm 
		{ 
			mov     eax, cr0 
				or     eax, 10000h 
				mov     cr0, eax 
				sti 
		} 
		KdPrint(("UnHook��ԭSSDT OK \n")); 
	}

	return;
}

