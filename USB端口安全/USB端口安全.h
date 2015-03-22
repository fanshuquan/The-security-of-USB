// USB端口安全.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once
#include "LOGIN.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CUSB端口安全App:
// 有关此类的实现，请参阅 USB端口安全.cpp
//

class CUSB端口安全App : public CWinApp
{
public:
	CUSB端口安全App();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CUSB端口安全App theApp;