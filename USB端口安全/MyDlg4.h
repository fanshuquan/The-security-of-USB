#pragma once
#include "afxwin.h"
#include "mystatic.h"


// CMyDlg4 �Ի���

class CMyDlg4 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg4)

public:
	CMyDlg4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg4();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CButton m_Btn1;
public:
	CButton m_Btn2;
public:
	CButton m_Btn3;
public:
	afx_msg void OnBnClickedButton1();
public:
	CStatic m_ps;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnStnClickedStaticPs();
public:
	afx_msg void OnStnClickedStaticNo();
};
