// USB�˿ڰ�ȫ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "LOGIN.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUSB�˿ڰ�ȫApp:
// �йش����ʵ�֣������ USB�˿ڰ�ȫ.cpp
//

class CUSB�˿ڰ�ȫApp : public CWinApp
{
public:
	CUSB�˿ڰ�ȫApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUSB�˿ڰ�ȫApp theApp;