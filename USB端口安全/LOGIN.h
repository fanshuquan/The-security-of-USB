#pragma once
#include "resource.h"
#include "afxwin.h"

// CLOGIN �Ի���

class CLOGIN : public CDialog
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLOGIN();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_pass;
public:
	virtual BOOL OnInitDialog();	
protected:
	virtual void OnCancel();
};
