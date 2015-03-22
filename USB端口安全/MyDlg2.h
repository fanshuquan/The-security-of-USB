#pragma once
#include "afxcmn.h"



// CMyDlg2 对话框

class CMyDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg2)

public:
	CMyDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlg2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listDrInfo;
public:
	virtual BOOL OnInitDialog();
	void EnumDrives();
	CString GetDriveTypeString(CString strDrive);
	void GetDriveSpaceInfo(UINT idx,CString strDrive);


public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnBnClickedButton2();
};
