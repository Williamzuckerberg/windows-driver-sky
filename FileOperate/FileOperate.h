//#include <ntdef.h>
#pragma INITCODE
VOID CreateFileTest() 
{
 NTSTATUS ntStatus;
 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING  SymbolFileName;
  KdPrint(("\n-----------------创建文件测试  --------------------!\n"));
 //初始化UNICODE_STRING字符串

   RtlInitUnicodeString(&SymbolFileName,L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
   //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\\CreateFileTest.txt");//可用此行替换上一行
 //初始化objectAttributes
 InitializeObjectAttributes(
	 &objectAttributes, //指定一个需要OBJECT_ATTRIBUTES结构地址
	 &SymbolFileName,//是一个UNICODE_STRING字串地址，指定需要操作对象名（在这里可以是符号链接名，或者设备名)
	 OBJ_CASE_INSENSITIVE, //指定此值表示 不区分大小写。
	 NULL, 
	 NULL );
 //创建文件
 ntStatus = ZwCreateFile( 
  &hfile, 
//PHANDLE类型指针 用于返回打开文件的句柄
  GENERIC_WRITE,
//ACCESS_MASK类型 此值用于描述打开文件操作（读，写，或者其它）
  &objectAttributes, 
//此值是OBJECT_ATTRIBUTES结构的地址，该结构包含要打开的文件名 需要用InitializeObjectAttributes进行初始化
  &iostatus,
//指向一个IO_STATUS_BLOCK结构，返回值之一 用于存放ZwCreateFile操作的结果状态
  NULL,
  //PLARGE_INTEGER 类型（64位整数指针）该数指定文件初始分配时的大小。该参数如果为NULL，那么文件长度将从0开始，随着写入而增长
  FILE_ATTRIBUTE_NORMAL,
  //此参数在驱动下指定为0或者FILE_ATTRIBUTE_NORMAL，如果文件不是被创建和覆盖写入 则此参数将被忽略
  FILE_SHARE_READ,
  //指定共享模式 有共享读FILE_SHARE_READ,写FILE_SHARE_WRITE,删除FILE_SHARE_DELETE这几中模式
  FILE_OPEN_IF,
  //此值表示 文件存在则打开 不存在则创建一个新的文件
  FILE_SYNCHRONOUS_IO_NONALERT,
  //指定文件创建或者打开的附加标志 FILE_SYNCHRONOUS_IO_NONALERT表示在文件中的所有操作均同步，并没有警报
  NULL, 
  //对于设备和中间驱动程序，此参数必须是NULL
  0 );  
 //对于设备和中间驱动程序，此参数必须是0
 if ( NT_SUCCESS(ntStatus))
 {
  KdPrint(("创建文件成功!\n"));
 }else
 {
  KdPrint(("创建文件失败!\n"));
 }

 //文件操作
 //.......

 //关闭文件句柄
 ZwClose(hfile);

}
VOID OpenFileTest() 
{
	NTSTATUS ntStatus;
	OBJECT_ATTRIBUTES objectAttributes;
	IO_STATUS_BLOCK iostatus;
	HANDLE hfile;
	UNICODE_STRING  SymbolFileName;
	KdPrint(("\n-----------------打开文件测试OpenFileTest  --------------------!\n"));
	//初始化UNICODE_STRING字符串

	RtlInitUnicodeString(&SymbolFileName,L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
	//RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\\CreateFileTest.txt");//可用此行替换上一行
	//初始化objectAttributes
	InitializeObjectAttributes(
		&objectAttributes, //指定一个需要OBJECT_ATTRIBUTES结构地址
		&SymbolFileName,//是一个UNICODE_STRING字串地址，指定需要操作对象名（在这里可以是符号链接名，或者设备名)
		OBJ_CASE_INSENSITIVE, //指定此值表示 不区分大小写。
		NULL, 
		NULL );
	//创建文件
	ntStatus = ZwCreateFile( 
		&hfile, 
		//PHANDLE类型指针 用于返回打开文件的句柄
		GENERIC_WRITE,
		//ACCESS_MASK类型 此值用于描述打开文件操作（读，写，或者其它）
		&objectAttributes, 
		//此值是OBJECT_ATTRIBUTES结构的地址，该结构包含要打开的文件名 需要用InitializeObjectAttributes进行初始化
		&iostatus,
		//指向一个IO_STATUS_BLOCK结构，返回值之一 用于存放ZwCreateFile操作的结果状态
		NULL,
		//PLARGE_INTEGER 类型（64位整数指针）该数指定文件初始分配时的大小。该参数如果为NULL，那么文件长度将从0开始，随着写入而增长
		FILE_ATTRIBUTE_NORMAL,
		//此参数在驱动下指定为0或者FILE_ATTRIBUTE_NORMAL，如果文件不是被创建和覆盖写入 则此参数将被忽略
		FILE_SHARE_READ,
		//指定共享模式 有共享读FILE_SHARE_READ,写FILE_SHARE_WRITE,删除FILE_SHARE_DELETE这几中模式
		FILE_OPEN,
		//此值表示 文件存在则打开 不存在则创建一个新的文件
		FILE_SYNCHRONOUS_IO_NONALERT,
		//指定文件创建或者打开的附加标志 FILE_SYNCHRONOUS_IO_NONALERT表示在文件中的所有操作均同步，并没有警报
		NULL, 
		//对于设备和中间驱动程序，此参数必须是NULL
		0 );  
	//对于设备和中间驱动程序，此参数必须是0
	if ( NT_SUCCESS(ntStatus))
	{
		KdPrint(("打开文件成功!hfile=%x\n",hfile));
	}else
	{
		KdPrint(("打开文件失败!hfile=%x\n",hfile));
	}

	//文件操作
	//.......

	//关闭文件句柄
	ZwClose(hfile);
	KdPrint(("\n-----------------打开文件测试OpenFileTest end --------------------!\n"));

}


#pragma INITCODE
VOID OpenFileTest2() 
{
	KdPrint(("\n-----------------创建文件测试2 ZwOpenFile---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //初始化UNICODE_STRING字符串
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");


 //初始化objectAttributes
 InitializeObjectAttributes(&objectAttributes, 
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE, 
  NULL, 
  NULL );

 //创建文件
 NTSTATUS ntStatus = ZwOpenFile(
  &hfile, 
  GENERIC_ALL,
  &objectAttributes, 
  &iostatus, 
  FILE_SHARE_READ|FILE_SHARE_WRITE,
  FILE_SYNCHRONOUS_IO_NONALERT);
 //对于设备和中间驱动程序，此参数必须是0
 if ( NT_SUCCESS(ntStatus))
 {
	 KdPrint(("打开文件成功!hfile=%x\n",hfile));
 }else
 {
	 KdPrint(("打开文件失败!hfile=%x\n",hfile));
 }

 //文件操作
 //.......

 //关闭文件句柄
 ZwClose(hfile);
 KdPrint(("\n-----------------创建文件测试2 ZwOpenFile---------------------!\n"));
}


#pragma INITCODE
VOID OpenFileTest1() 
{
	KdPrint(("\n-----------------打开文件测试 ZwCreateFile---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //初始化UNICODE_STRING字符串
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //初始化objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//对大小写敏感 
  NULL, 
  NULL );

 //创建文件
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_READ,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN,//对文件打开，如果不存在则返回错误 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );
 if ( NT_SUCCESS(ntStatus))
 {
  KdPrint(("打开文件测试 ZwCreateFile 成功!\n"));
 }else
 {
  KdPrint(("打开文件测试 ZwCreateFile 失败!\n"));
 }

 //文件操作
 //.......

 //关闭文件句柄
 ZwClose(hfile);
}


#pragma INITCODE
VOID FileAttributeTest() 
{
	KdPrint(("\n-----------------ZwQueryInformationFile  ZwSetInformationFile 测试 ---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //初始化UNICODE_STRING字符串
 //RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\CreateFileTest.txt");

 //初始化objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//对大小写敏感 
  NULL, 
  NULL );

 //创建文件
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_ALL,
  &objectAttributes, 
  &iostatus, 
  0,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN_IF,//对文件打开，如果不存在则返回错误 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("打开文件成功.\n"));
 }

 FILE_STANDARD_INFORMATION fsi;
 //读取文件长度
 
 ntStatus = ZwQueryInformationFile(hfile,
  &iostatus,
  &fsi,
  sizeof(FILE_STANDARD_INFORMATION),
  FileStandardInformation);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("文件长度 :%u\n",fsi.EndOfFile.QuadPart));
 }  
 
//读出文件属性
 FILE_BASIC_INFORMATION fbi;
  ZwQueryInformationFile(hfile,
	 &iostatus,
	 &fbi,
	 sizeof(FILE_BASIC_INFORMATION),
	 FileBasicInformation); 
//修改文件属性
 fbi.FileAttributes=FILE_ATTRIBUTE_READONLY;//|FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_NORMAL;
 ntStatus = ZwSetInformationFile(hfile,
  &iostatus,
  &fbi,
  sizeof(FILE_BASIC_INFORMATION),
  FileBasicInformation);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("设置文件  属性成功.\n"));
 } else
 {
 KdPrint(("设置文件  属性失败ntStatus=%x\n",ntStatus));
 }  

 //关闭文件句柄
 ZwClose(hfile);
}


#pragma INITCODE
VOID WriteFileTest() 
{
 KdPrint(("\n---------------------ZwWriteFile写文件测试--------------------\n"));
 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //初始化UNICODE_STRING字符串
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //初始化objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//对大小写敏感 
  NULL, 
  NULL );

 //创建文件
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_WRITE,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN_IF,//即使存在该文件，也创建 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );
#define BUFFER_SIZE 30
 PCHAR pBuffer = (PCHAR)ExAllocatePool(PagedPool,BUFFER_SIZE);
 //构造要填充的数据
 RtlFillMemory(pBuffer,BUFFER_SIZE,'s');//www.yjxsoft.comssssssssssssxxxxxx
 //strcpy(pBuffer,"www.yjxsoft.com");
 RtlCopyMemory(pBuffer,"www.yjxsoft.com",15);

 KdPrint(("即将写入 %d 字节\n",BUFFER_SIZE));
 //写文件ZwQueryInfomationfile
 LARGE_INTEGER sl;
 sl.QuadPart=0i64;
 ZwWriteFile(hfile,NULL,NULL,NULL,&iostatus,pBuffer,30,&sl,NULL);
 KdPrint(("成功写入 %d 字节\n",iostatus.Information));

 
 //构造要填充的数据
 RtlFillMemory(pBuffer,BUFFER_SIZE,'x');

 KdPrint(("成功写入 %d 字节\n",BUFFER_SIZE));
 //追加数据
 LARGE_INTEGER number;
 number.QuadPart =30i64;//设置文件指针
 //对文件进行附加写
 ZwWriteFile(hfile,NULL,NULL,NULL,&iostatus,pBuffer,BUFFER_SIZE,&number,NULL);
 KdPrint(("追加写入 %d 字节\n",iostatus.Information));
 
 //关闭文件句柄
 ZwClose(hfile);

 ExFreePool(pBuffer);
}
#pragma INITCODE
VOID ReadFileTest() 
{
KdPrint(("\n---------------------ZwReadFile写文件测试--------------------\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //初始化UNICODE_STRING字符串
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //初始化objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//对大小写敏感 
  NULL, 
  NULL );

 //创建文件
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_READ,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, //常规属性
  FILE_SHARE_READ,//共享读
  FILE_OPEN,//有文件存在则打开，不存在则报错
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );

 if (!NT_SUCCESS(ntStatus))
 {
  KdPrint(("文件不存在!\n"));
  return;
 }

 FILE_STANDARD_INFORMATION fsi;
 //读取文件长度
 ntStatus = ZwQueryInformationFile(hfile,
  &iostatus,
  &fsi,
  sizeof(FILE_STANDARD_INFORMATION),
  FileStandardInformation);

 KdPrint(("共读取 %d 字节\n",fsi.EndOfFile.QuadPart));

 //为读取的文件分配缓冲区
 PUCHAR pBuffer = (PUCHAR)ExAllocatePool(PagedPool,
  (LONG)fsi.EndOfFile.QuadPart);

 //读取文件
 ZwReadFile(hfile,NULL,
  NULL,NULL,
  &iostatus,
  pBuffer,
  (LONG)fsi.EndOfFile.QuadPart,
  NULL,NULL);
 KdPrint(("实际读取 %d 字节\n",iostatus.Information));
 //显示实际读取内容
 KdPrint(("\n 成功读取内容为:%s \n",pBuffer));
 //关闭文件句柄
 ZwClose(hfile);

 //释放缓冲区
 ExFreePool(pBuffer);
}



#pragma INITCODE
VOID FileTestAll() 
{
//创建文件实验
	CreateFileTest();
//打开文件实验
	OpenFileTest();
//设置文件属性
	FileAttributeTest();
//写文件、读文件实验
	WriteFileTest();
	ReadFileTest();

}
