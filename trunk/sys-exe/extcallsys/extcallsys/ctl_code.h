/*#ifndef  CTL_CODE
#pragma message("\n\n------------------exe 模式.please include winioctl.h")
#include<winioctl.h> //CTL_CODE
#else
#pragma message("\n\n------------------sys 模式.no need to include winioctl.h")
#endif*/
#define add_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x800, 	METHOD_BUFFERED,FILE_ANY_ACCESS)
#define sub_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x801, 	METHOD_BUFFERED,FILE_ANY_ACCESS)

//有四种方式访问模式
//#define METHOD_BUFFERED                 0  缓冲区方式
//#define METHOD_IN_DIRECT                1  直接访问方式
//#define METHOD_OUT_DIRECT               2  直接访问方式
//#define METHOD_NEITHER                  3  其它访问方式