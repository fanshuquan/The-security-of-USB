#pragma once


// CMyDlg5 �Ի���

class CMyDlg5 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg5)

public:
	CMyDlg5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg5();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticReg();
public:
	afx_msg void OnStnClickedStaticCmd();
public:
	afx_msg void OnStnClickedStaticNo1();
public:
	afx_msg void OnStnClickedStaticNo2();
public:
	afx_msg void OnStnClickedStaticNo3();
public:
	afx_msg void OnStnClickedStaticTask();
};
