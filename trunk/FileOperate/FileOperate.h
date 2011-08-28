//#include <ntdef.h>
#pragma INITCODE
VOID CreateFileTest() 
{
 NTSTATUS ntStatus;
 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING  SymbolFileName;
  KdPrint(("\n-----------------�����ļ�����  --------------------!\n"));
 //��ʼ��UNICODE_STRING�ַ���

   RtlInitUnicodeString(&SymbolFileName,L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
   //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\\CreateFileTest.txt");//���ô����滻��һ��
 //��ʼ��objectAttributes
 InitializeObjectAttributes(
	 &objectAttributes, //ָ��һ����ҪOBJECT_ATTRIBUTES�ṹ��ַ
	 &SymbolFileName,//��һ��UNICODE_STRING�ִ���ַ��ָ����Ҫ����������������������Ƿ����������������豸��)
	 OBJ_CASE_INSENSITIVE, //ָ����ֵ��ʾ �����ִ�Сд��
	 NULL, 
	 NULL );
 //�����ļ�
 ntStatus = ZwCreateFile( 
  &hfile, 
//PHANDLE����ָ�� ���ڷ��ش��ļ��ľ��
  GENERIC_WRITE,
//ACCESS_MASK���� ��ֵ�����������ļ�����������д������������
  &objectAttributes, 
//��ֵ��OBJECT_ATTRIBUTES�ṹ�ĵ�ַ���ýṹ����Ҫ�򿪵��ļ��� ��Ҫ��InitializeObjectAttributes���г�ʼ��
  &iostatus,
//ָ��һ��IO_STATUS_BLOCK�ṹ������ֵ֮һ ���ڴ��ZwCreateFile�����Ľ��״̬
  NULL,
  //PLARGE_INTEGER ���ͣ�64λ����ָ�룩����ָ���ļ���ʼ����ʱ�Ĵ�С���ò������ΪNULL����ô�ļ����Ƚ���0��ʼ������д�������
  FILE_ATTRIBUTE_NORMAL,
  //�˲�����������ָ��Ϊ0����FILE_ATTRIBUTE_NORMAL������ļ����Ǳ������͸���д�� ��˲�����������
  FILE_SHARE_READ,
  //ָ������ģʽ �й����FILE_SHARE_READ,дFILE_SHARE_WRITE,ɾ��FILE_SHARE_DELETE�⼸��ģʽ
  FILE_OPEN_IF,
  //��ֵ��ʾ �ļ�������� �������򴴽�һ���µ��ļ�
  FILE_SYNCHRONOUS_IO_NONALERT,
  //ָ���ļ��������ߴ򿪵ĸ��ӱ�־ FILE_SYNCHRONOUS_IO_NONALERT��ʾ���ļ��е����в�����ͬ������û�о���
  NULL, 
  //�����豸���м��������򣬴˲���������NULL
  0 );  
 //�����豸���м��������򣬴˲���������0
 if ( NT_SUCCESS(ntStatus))
 {
  KdPrint(("�����ļ��ɹ�!\n"));
 }else
 {
  KdPrint(("�����ļ�ʧ��!\n"));
 }

 //�ļ�����
 //.......

 //�ر��ļ����
 ZwClose(hfile);

}
VOID OpenFileTest() 
{
	NTSTATUS ntStatus;
	OBJECT_ATTRIBUTES objectAttributes;
	IO_STATUS_BLOCK iostatus;
	HANDLE hfile;
	UNICODE_STRING  SymbolFileName;
	KdPrint(("\n-----------------���ļ�����OpenFileTest  --------------------!\n"));
	//��ʼ��UNICODE_STRING�ַ���

	RtlInitUnicodeString(&SymbolFileName,L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
	//RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\\CreateFileTest.txt");//���ô����滻��һ��
	//��ʼ��objectAttributes
	InitializeObjectAttributes(
		&objectAttributes, //ָ��һ����ҪOBJECT_ATTRIBUTES�ṹ��ַ
		&SymbolFileName,//��һ��UNICODE_STRING�ִ���ַ��ָ����Ҫ����������������������Ƿ����������������豸��)
		OBJ_CASE_INSENSITIVE, //ָ����ֵ��ʾ �����ִ�Сд��
		NULL, 
		NULL );
	//�����ļ�
	ntStatus = ZwCreateFile( 
		&hfile, 
		//PHANDLE����ָ�� ���ڷ��ش��ļ��ľ��
		GENERIC_WRITE,
		//ACCESS_MASK���� ��ֵ�����������ļ�����������д������������
		&objectAttributes, 
		//��ֵ��OBJECT_ATTRIBUTES�ṹ�ĵ�ַ���ýṹ����Ҫ�򿪵��ļ��� ��Ҫ��InitializeObjectAttributes���г�ʼ��
		&iostatus,
		//ָ��һ��IO_STATUS_BLOCK�ṹ������ֵ֮һ ���ڴ��ZwCreateFile�����Ľ��״̬
		NULL,
		//PLARGE_INTEGER ���ͣ�64λ����ָ�룩����ָ���ļ���ʼ����ʱ�Ĵ�С���ò������ΪNULL����ô�ļ����Ƚ���0��ʼ������д�������
		FILE_ATTRIBUTE_NORMAL,
		//�˲�����������ָ��Ϊ0����FILE_ATTRIBUTE_NORMAL������ļ����Ǳ������͸���д�� ��˲�����������
		FILE_SHARE_READ,
		//ָ������ģʽ �й����FILE_SHARE_READ,дFILE_SHARE_WRITE,ɾ��FILE_SHARE_DELETE�⼸��ģʽ
		FILE_OPEN,
		//��ֵ��ʾ �ļ�������� �������򴴽�һ���µ��ļ�
		FILE_SYNCHRONOUS_IO_NONALERT,
		//ָ���ļ��������ߴ򿪵ĸ��ӱ�־ FILE_SYNCHRONOUS_IO_NONALERT��ʾ���ļ��е����в�����ͬ������û�о���
		NULL, 
		//�����豸���м��������򣬴˲���������NULL
		0 );  
	//�����豸���м��������򣬴˲���������0
	if ( NT_SUCCESS(ntStatus))
	{
		KdPrint(("���ļ��ɹ�!hfile=%x\n",hfile));
	}else
	{
		KdPrint(("���ļ�ʧ��!hfile=%x\n",hfile));
	}

	//�ļ�����
	//.......

	//�ر��ļ����
	ZwClose(hfile);
	KdPrint(("\n-----------------���ļ�����OpenFileTest end --------------------!\n"));

}


#pragma INITCODE
VOID OpenFileTest2() 
{
	KdPrint(("\n-----------------�����ļ�����2 ZwOpenFile---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //��ʼ��UNICODE_STRING�ַ���
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");


 //��ʼ��objectAttributes
 InitializeObjectAttributes(&objectAttributes, 
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE, 
  NULL, 
  NULL );

 //�����ļ�
 NTSTATUS ntStatus = ZwOpenFile(
  &hfile, 
  GENERIC_ALL,
  &objectAttributes, 
  &iostatus, 
  FILE_SHARE_READ|FILE_SHARE_WRITE,
  FILE_SYNCHRONOUS_IO_NONALERT);
 //�����豸���м��������򣬴˲���������0
 if ( NT_SUCCESS(ntStatus))
 {
	 KdPrint(("���ļ��ɹ�!hfile=%x\n",hfile));
 }else
 {
	 KdPrint(("���ļ�ʧ��!hfile=%x\n",hfile));
 }

 //�ļ�����
 //.......

 //�ر��ļ����
 ZwClose(hfile);
 KdPrint(("\n-----------------�����ļ�����2 ZwOpenFile---------------------!\n"));
}


#pragma INITCODE
VOID OpenFileTest1() 
{
	KdPrint(("\n-----------------���ļ����� ZwCreateFile---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //��ʼ��UNICODE_STRING�ַ���
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //��ʼ��objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//�Դ�Сд���� 
  NULL, 
  NULL );

 //�����ļ�
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_READ,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN,//���ļ��򿪣�����������򷵻ش��� 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );
 if ( NT_SUCCESS(ntStatus))
 {
  KdPrint(("���ļ����� ZwCreateFile �ɹ�!\n"));
 }else
 {
  KdPrint(("���ļ����� ZwCreateFile ʧ��!\n"));
 }

 //�ļ�����
 //.......

 //�ر��ļ����
 ZwClose(hfile);
}


#pragma INITCODE
VOID FileAttributeTest() 
{
	KdPrint(("\n-----------------ZwQueryInformationFile  ZwSetInformationFile ���� ---------------------!\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //��ʼ��UNICODE_STRING�ַ���
 //RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\1.txt");
 RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\CreateFileTest.txt");

 //��ʼ��objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//�Դ�Сд���� 
  NULL, 
  NULL );

 //�����ļ�
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_ALL,
  &objectAttributes, 
  &iostatus, 
  0,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN_IF,//���ļ��򿪣�����������򷵻ش��� 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("���ļ��ɹ�.\n"));
 }

 FILE_STANDARD_INFORMATION fsi;
 //��ȡ�ļ�����
 
 ntStatus = ZwQueryInformationFile(hfile,
  &iostatus,
  &fsi,
  sizeof(FILE_STANDARD_INFORMATION),
  FileStandardInformation);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("�ļ����� :%u\n",fsi.EndOfFile.QuadPart));
 }  
 
//�����ļ�����
 FILE_BASIC_INFORMATION fbi;
  ZwQueryInformationFile(hfile,
	 &iostatus,
	 &fbi,
	 sizeof(FILE_BASIC_INFORMATION),
	 FileBasicInformation); 
//�޸��ļ�����
 fbi.FileAttributes=FILE_ATTRIBUTE_READONLY;//|FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_NORMAL;
 ntStatus = ZwSetInformationFile(hfile,
  &iostatus,
  &fbi,
  sizeof(FILE_BASIC_INFORMATION),
  FileBasicInformation);
 if (NT_SUCCESS(ntStatus))
 {
  KdPrint(("�����ļ�  ���Գɹ�.\n"));
 } else
 {
 KdPrint(("�����ļ�  ����ʧ��ntStatus=%x\n",ntStatus));
 }  

 //�ر��ļ����
 ZwClose(hfile);
}


#pragma INITCODE
VOID WriteFileTest() 
{
 KdPrint(("\n---------------------ZwWriteFileд�ļ�����--------------------\n"));
 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //��ʼ��UNICODE_STRING�ַ���
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //��ʼ��objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//�Դ�Сд���� 
  NULL, 
  NULL );

 //�����ļ�
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_WRITE,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, 
  FILE_SHARE_WRITE,
  FILE_OPEN_IF,//��ʹ���ڸ��ļ���Ҳ���� 
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );
#define BUFFER_SIZE 30
 PCHAR pBuffer = (PCHAR)ExAllocatePool(PagedPool,BUFFER_SIZE);
 //����Ҫ��������
 RtlFillMemory(pBuffer,BUFFER_SIZE,'s');//www.yjxsoft.comssssssssssssxxxxxx
 //strcpy(pBuffer,"www.yjxsoft.com");
 RtlCopyMemory(pBuffer,"www.yjxsoft.com",15);

 KdPrint(("����д�� %d �ֽ�\n",BUFFER_SIZE));
 //д�ļ�ZwQueryInfomationfile
 LARGE_INTEGER sl;
 sl.QuadPart=0i64;
 ZwWriteFile(hfile,NULL,NULL,NULL,&iostatus,pBuffer,30,&sl,NULL);
 KdPrint(("�ɹ�д�� %d �ֽ�\n",iostatus.Information));

 
 //����Ҫ��������
 RtlFillMemory(pBuffer,BUFFER_SIZE,'x');

 KdPrint(("�ɹ�д�� %d �ֽ�\n",BUFFER_SIZE));
 //׷������
 LARGE_INTEGER number;
 number.QuadPart =30i64;//�����ļ�ָ��
 //���ļ����и���д
 ZwWriteFile(hfile,NULL,NULL,NULL,&iostatus,pBuffer,BUFFER_SIZE,&number,NULL);
 KdPrint(("׷��д�� %d �ֽ�\n",iostatus.Information));
 
 //�ر��ļ����
 ZwClose(hfile);

 ExFreePool(pBuffer);
}
#pragma INITCODE
VOID ReadFileTest() 
{
KdPrint(("\n---------------------ZwReadFileд�ļ�����--------------------\n"));

 OBJECT_ATTRIBUTES objectAttributes;
 IO_STATUS_BLOCK iostatus;
 HANDLE hfile;
 UNICODE_STRING SymbolFileName;

 //��ʼ��UNICODE_STRING�ַ���
 RtlInitUnicodeString( &SymbolFileName, L"\\Device\\HarddiskVolume1\\CreateFileTest.txt");
 //RtlInitUnicodeString( &SymbolFileName,  L"\\??\\C:\\1.txt");

 //��ʼ��objectAttributes
 InitializeObjectAttributes(&objectAttributes,
  &SymbolFileName,
  OBJ_CASE_INSENSITIVE,//�Դ�Сд���� 
  NULL, 
  NULL );

 //�����ļ�
 NTSTATUS ntStatus = ZwCreateFile( &hfile, 
  GENERIC_READ,
  &objectAttributes, 
  &iostatus, 
  NULL,
  FILE_ATTRIBUTE_NORMAL, //��������
  FILE_SHARE_READ,//�����
  FILE_OPEN,//���ļ�������򿪣��������򱨴�
  FILE_SYNCHRONOUS_IO_NONALERT, 
  NULL, 
  0 );

 if (!NT_SUCCESS(ntStatus))
 {
  KdPrint(("�ļ�������!\n"));
  return;
 }

 FILE_STANDARD_INFORMATION fsi;
 //��ȡ�ļ�����
 ntStatus = ZwQueryInformationFile(hfile,
  &iostatus,
  &fsi,
  sizeof(FILE_STANDARD_INFORMATION),
  FileStandardInformation);

 KdPrint(("����ȡ %d �ֽ�\n",fsi.EndOfFile.QuadPart));

 //Ϊ��ȡ���ļ����仺����
 PUCHAR pBuffer = (PUCHAR)ExAllocatePool(PagedPool,
  (LONG)fsi.EndOfFile.QuadPart);

 //��ȡ�ļ�
 ZwReadFile(hfile,NULL,
  NULL,NULL,
  &iostatus,
  pBuffer,
  (LONG)fsi.EndOfFile.QuadPart,
  NULL,NULL);
 KdPrint(("ʵ�ʶ�ȡ %d �ֽ�\n",iostatus.Information));
 //��ʾʵ�ʶ�ȡ����
 KdPrint(("\n �ɹ���ȡ����Ϊ:%s \n",pBuffer));
 //�ر��ļ����
 ZwClose(hfile);

 //�ͷŻ�����
 ExFreePool(pBuffer);
}



#pragma INITCODE
VOID FileTestAll() 
{
//�����ļ�ʵ��
	CreateFileTest();
//���ļ�ʵ��
	OpenFileTest();
//�����ļ�����
	FileAttributeTest();
//д�ļ������ļ�ʵ��
	WriteFileTest();
	ReadFileTest();

}
