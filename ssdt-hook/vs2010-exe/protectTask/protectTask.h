
// protectTask.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CprotectTaskApp:
// �йش����ʵ�֣������ protectTask.cpp
//

class CprotectTaskApp : public CWinApp
{
public:
	CprotectTaskApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CprotectTaskApp theApp;