#include <ntddk.h>

VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject);

int DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING RegistryPath)
{
    KdPrint(("Hello Driver World 驱动加载成功"));
    KdPrint(("记得要用双括号，在debug版本中KdPrint会用DbgPrint代替，release版就不做任何事"));
    DbgPrint("这是最简单的驱动");
    pDriverObject->DriverUnload = Driver_Unload;
    return (1);
}

VOID Driver_Unload(IN PDRIVER_OBJECT pDriverObject)
{
    KdPrint(("Hello Driver World 驱动卸载成功"));
}