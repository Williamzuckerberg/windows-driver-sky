
// sysLoader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsysLoaderApp:
// �йش����ʵ�֣������ sysLoader.cpp
//

class CsysLoaderApp : public CWinApp
{
public:
	CsysLoaderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsysLoaderApp theApp;