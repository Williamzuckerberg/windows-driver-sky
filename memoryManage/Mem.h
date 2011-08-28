#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#include <NTDDK.h> //���������Ҫ��C��ʽ�����ͷ�ļ�
#ifdef __cplusplus
}
#endif 
//����new��delete������
//����new
 
void * __cdecl operator new(size_t size,POOL_TYPE PoolType=PagedPool)
{
	KdPrint(("global operator new\n"));
	KdPrint(("Allocate size :%d\n",size));
	return ExAllocatePoolWithTag(PagedPool,size, 1);
}
//����delete 
void __cdecl operator delete(void* pointer)
{
	KdPrint(("Global delete operator\n"));
	ExFreePool(pointer);
}
  

#pragma INITCODE
VOID memtest()
{   
	VOID UNALIGNED *d;
	VOID UNALIGNED *s;
	SIZE_T Length=8;
	ULONG ulRet;
	char *buffer=new (PagedPool)  char[111];//
	delete buffer;

 //Ϊsָ������СΪ8�ֽڵ��ں� �ڴ�
 s=ExAllocatePoolWithTag(PagedPool,Length, 1);
 KdPrint(("s=%x \n",(int*)s));
 //  __asm int 3 db
 //Ϊdָ������СΪ8�ֽڵ��ں� �ڴ�
 d=ExAllocatePoolWithTag(PagedPool,Length, 1);
 //  __asm int 3 db
  KdPrint(("d=%x \n",(int*)d));
  //��0�����sָ�� ָ����ڴ� ��䳤��ΪLength=8
  RtlFillMemory(s,Length,'s');
  //  __asm int 3 db 
   KdPrint(("RtlFillMemory 1 \n" ));
  //����Sָ��ָ������ݵ� D��ַ ���Ƴ���ΪLength=8
  RtlCopyMemory(d,s,Length); //memcpy
//  __asm int 3
   KdPrint(("RtlCopyMemory s to d \n" ));
  //����Sָ��ָ������ݵ� D��ַ ���Ƴ���ΪLength=8
  RtlCopyBytes(d,s,Length);

 

  //�ж��ڴ��Ƿ�һ��
 ulRet = RtlCompareMemory(d,s,Length); // ����
//RtlEqualMemory(d,s,Length);// �ʹ˺���ʱ����build
  if (ulRet==Length) //�������ֵ
  {
   KdPrint(("111 D��S �ڴ����ͬ.\n"));
  }else KdPrint(("111 D��S �ڴ�鲻��ͬ\n"));

  //���Sָ��ָ���ַ
  RtlZeroBytes(s,Length);

  ulRet = RtlCompareMemory(d,s,Length);

 if (ulRet==Length) //�������ֵ
	{		
	KdPrint(("222 D��S �ڴ����ͬ.\n"));
	}else KdPrint(("222 D��S �ڴ�鲻��ͬ\n"));

  ExFreePool(s) ;
  return;

}
 
