/*#ifndef  CTL_CODE
#pragma message("\n\n------------------exe ģʽ.please include winioctl.h")
#include<winioctl.h> //CTL_CODE
#else
#pragma message("\n\n------------------sys ģʽ.no need to include winioctl.h")
#endif*/
#define add_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x800, 	METHOD_BUFFERED,FILE_ANY_ACCESS)
#define sub_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x801, 	METHOD_BUFFERED,FILE_ANY_ACCESS)

//�����ַ�ʽ����ģʽ
//#define METHOD_BUFFERED                 0  ��������ʽ
//#define METHOD_IN_DIRECT                1  ֱ�ӷ��ʷ�ʽ
//#define METHOD_OUT_DIRECT               2  ֱ�ӷ��ʷ�ʽ
//#define METHOD_NEITHER                  3  �������ʷ�ʽ