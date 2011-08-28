#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#include <NTDDK.h> //这里包含需要用C方式编译的头文件
#ifdef __cplusplus
}
#endif 
//重载new和delete操作符
//重载new
 
void * __cdecl operator new(size_t size,POOL_TYPE PoolType=PagedPool)
{
	KdPrint(("global operator new\n"));
	KdPrint(("Allocate size :%d\n",size));
	return ExAllocatePoolWithTag(PagedPool,size, 1);
}
//重载delete 
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

 //为s指针分配大小为8字节的内核 内存
 s=ExAllocatePoolWithTag(PagedPool,Length, 1);
 KdPrint(("s=%x \n",(int*)s));
 //  __asm int 3 db
 //为d指针分配大小为8字节的内核 内存
 d=ExAllocatePoolWithTag(PagedPool,Length, 1);
 //  __asm int 3 db
  KdPrint(("d=%x \n",(int*)d));
  //用0来填充s指针 指向的内存 填充长度为Length=8
  RtlFillMemory(s,Length,'s');
  //  __asm int 3 db 
   KdPrint(("RtlFillMemory 1 \n" ));
  //复制S指针指向的内容到 D地址 复制长度为Length=8
  RtlCopyMemory(d,s,Length); //memcpy
//  __asm int 3
   KdPrint(("RtlCopyMemory s to d \n" ));
  //复制S指针指向的内容到 D地址 复制长度为Length=8
  RtlCopyBytes(d,s,Length);

 

  //判断内存是否一致
 ulRet = RtlCompareMemory(d,s,Length); // 可用
//RtlEqualMemory(d,s,Length);// 和此函数时请用build
  if (ulRet==Length) //如果返回值
  {
   KdPrint(("111 D和S 内存块相同.\n"));
  }else KdPrint(("111 D和S 内存块不相同\n"));

  //清空S指针指向地址
  RtlZeroBytes(s,Length);

  ulRet = RtlCompareMemory(d,s,Length);

 if (ulRet==Length) //如果返回值
	{		
	KdPrint(("222 D和S 内存块相同.\n"));
	}else KdPrint(("222 D和S 内存块不相同\n"));

  ExFreePool(s) ;
  return;

}
 
