#pragma once
#include "afxwin.h"



// CMyDlg6 �Ի���

class CMyDlg6 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg6)

public:
	CMyDlg6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg6();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
