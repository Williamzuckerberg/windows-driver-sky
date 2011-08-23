// execallsys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "ctl_code.h"

int add(HANDLE hDevice, int a,int b)
{

	int port[2];
	int bufret;
	ULONG dwWrite;
	port[0]=a;
	port[1]=b;

	DeviceIoControl(hDevice, add_code , &port, 8, &bufret, 4, &dwWrite, NULL);
	return bufret;

}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hDevice = 
		CreateFile(L"\\\\.\\secondSysDevice", //\\??\\firstSysDevice
		GENERIC_READ | GENERIC_WRITE,
		0,		// share mode none
		NULL,	// no security
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL );		// no template
	printf("start\n");
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("获取驱动句柄失败: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
		getchar();
		return -1;
	}
	int a=9955;
	int b=33;
	int r=add(hDevice,a,b);
	printf("%d+%d=%d \n",a,b,r);
	getchar();
	return 0;
}

