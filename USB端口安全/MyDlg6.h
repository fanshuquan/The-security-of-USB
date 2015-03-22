#pragma once
#include "afxwin.h"



// CMyDlg6 对话框

class CMyDlg6 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg6)

public:
	CMyDlg6(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlg6();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_BtnAutorun;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton1();
public:
	CEdit m_OldPass;
public:
	CEdit m_NewPass;
public:
	afx_msg void OnBnClickedButton3();
};
