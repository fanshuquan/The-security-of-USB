// USB�˿ڰ�ȫDlg.h : ͷ�ļ�
//

#pragma once
#define WM_TRAYICON_MSG WM_USER+1
#include "TrueColorToolBar.h"
#include "MyStatic.h"
#include "MyDlg.h"
#include "MyDlg2.h"
#include "MyDlg3.h"
#include "MyDlg4.h"
#include "MyDlg5.h"
#include "MyDlg6.h"
#include "MyDlg7.h"

#include "SkinPPLIB/SkinPPWTL.h"


// CUSB�˿ڰ�ȫDlg �Ի���
class CUSB�˿ڰ�ȫDlg : public CDialog
{
// ����
public:
	CUSB�˿ڰ�ȫDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_USB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatusBarCtrl m_wndStatusBarCtrl;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedCancel();
public:NOTIFYICONDATA m_sIcon;
public:
	afx_msg void OnMenuHide();
public:
	afx_msg void OnMenuShow();
public:
	afx_msg void OnMenuExit();
public:
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
public:
	CTrueColorToolBar m_wndToolBar;
public:
	CMyStatic m_MyStatic;
	afx_msg void OnToolfun();
	afx_msg void OnTool1fun();
	afx_msg void OnTool2fun();
	afx_msg void OnTool3fun();
	afx_msg void OnTool4fun();
	afx_msg void OnTool5fun();
	afx_msg void OnTool6fun();
public:
	CRect rec;
	CMyDlg *m_mydlg;
	CMyDlg2 *m_mydlg2;
	CMyDlg3 *m_mydlg3;
	CMyDlg4 *m_mydlg4;
	CMyDlg5 *m_mydlg5;
//	CMyDlg6 *m_mydlg6;
	CMyDlg7 *m_mydlg7;
};
