#pragma once
#include "resource.h"
#include "afxwin.h"

// CLOGIN 对话框

class CLOGIN : public CDialog
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLOGIN();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_pass;
public:
	virtual BOOL OnInitDialog();	
protected:
	virtual void OnCancel();
};
