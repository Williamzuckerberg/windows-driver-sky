#include <ntddk.h>

VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);

int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
    KdPrint(("Hello Driver World �������سɹ�"));
    KdPrint(("�ǵ�Ҫ��˫���ţ���debug�汾��KdPrint����DbgPrint���棬release��Ͳ����κ���"));
    DbgPrint("������򵥵�����");
    pDriverObject->DriverUnload = Driver_Unload;
    return (1);
}

VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject)
{
    KdPrint(("Hello Driver World ����ж�سɹ�"));
}