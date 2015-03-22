// MyDlg5.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg5.h"


// CMyDlg5 对话框

IMPLEMENT_DYNAMIC(CMyDlg5, CDialog)

CMyDlg5::CMyDlg5(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg5::IDD, pParent)
{

}

CMyDlg5::~CMyDlg5()
{
}

void CMyDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg5, CDialog)
	ON_STN_CLICKED(IDC_STATIC_REG, &CMyDlg5::OnStnClickedStaticReg)
	ON_STN_CLICKED(IDC_STATIC_CMD, &CMyDlg5::OnStnClickedStaticCmd)
	ON_STN_CLICKED(IDC_STATIC_NO1, &CMyDlg5::OnStnClickedStaticNo1)
	ON_STN_CLICKED(IDC_STATIC_NO2, &CMyDlg5::OnStnClickedStaticNo2)
	ON_STN_CLICKED(IDC_STATIC_NO3, &CMyDlg5::OnStnClickedStaticNo3)
	ON_STN_CLICKED(IDC_STATIC_TASK, &CMyDlg5::OnStnClickedStaticTask)
END_MESSAGE_MAP()


// CMyDlg5 消息处理程序

void CMyDlg5::OnStnClickedStaticReg()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=0;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableRegistryTools"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("修复成功!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg5::OnStnClickedStaticCmd()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=0;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Policies\\Microsoft\\Windows\\system"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableCMD"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("修复成功!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg5::OnStnClickedStaticNo1()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=1;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableRegistryTools"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("已禁止!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg5::OnStnClickedStaticNo2()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=1;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Policies\\Microsoft\\Windows\\system"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableCMD"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("已禁止!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg5::OnStnClickedStaticNo3()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=1;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableTaskMgr"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("已禁止!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg5::OnStnClickedStaticTask()
{
	// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	DWORD szValue=0;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableTaskMgr"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("修复成功!"));
	}		
	RegCloseKey(hKey);
}
