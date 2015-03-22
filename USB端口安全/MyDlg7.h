#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CHOOSE.h"
extern CString strpath;
extern CString strfile;

#include <Tlhelp32.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")


// CMyDlg7 对话框

class CMyDlg7 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg7)

public:
	CMyDlg7(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlg7();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
public:
	void EnumDrives();
public:
	CString GetDriveTypeString(CString strDrive);
public:
	CListBox m_ListBox;
public:
	virtual BOOL OnInitDialog();
public:
	void FindAutorun(TCHAR strDrive);
// public:
// 	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
public:
	void dosomething();
public:
	CListCtrl m_LiProgress;
public:
	BOOL GetProcessList();
	BOOL AdjustPrivileges();
public:
	afx_msg void OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnMRefreshList();
public:
	afx_msg void OnMEdnTask();
public:
	afx_msg void OnMFindExe();
public:
	afx_msg void OnMCopyPath();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton5();
	CString loginpath;
};