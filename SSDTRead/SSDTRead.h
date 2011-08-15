#include <ntddk.h>

#define INITCODE code_seg("INIT")
#define PAGECODE code_seg("PAGE")

typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase; //System Service Dispatch Table �Ļ���ַ  
	PVOID ServiceCounterTable;
	//������ SSDT ��ÿ�����񱻵��ô����ļ����������������һ����sysenter ���¡� 
	unsigned int NumberOfServices;//�� ServiceTableBase �����ķ������Ŀ��  
	PVOID ParamTableBase; //����ÿ��ϵͳ��������ֽ�����Ļ���ַ-ϵͳ��������� 
}*PServiceDescriptorTable;  
extern PServiceDescriptorTable KeServiceDescriptorTable;

#pragma INITCODE
VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateTheDevice(IN PDRIVER_OBJECT pDeviceObject);
NTSTATUS ddk_DispatchRoutine_CONTROL(IN PDEVICE_OBJECT pDevobj,IN PIRP pIrp	);//��ǲ����

//��ȡ��ǰSSDT�к����ĵ�ַ
VOID asmReadSSDT();
VOID cReadSSDT();

//��ȡϵͳ�к����ĵ�ַ
VOID getSystemCallAddr();