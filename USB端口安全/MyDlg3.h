#pragma once
#include "afxcmn.h"


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
// CMyDlg3 �Ի���

class CMyDlg3 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg3)

public:
	CMyDlg3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg3();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void QueryKey(HKEY hKey,TCHAR stri[]);
	//void QueryKeyV(HKEY hKey,TCHAR stri[]);
	CString finder(HKEY hvKey,int i,CString str);
public:
	CListCtrl m_historylist;
public:
	virtual BOOL OnInitDialog();
};
