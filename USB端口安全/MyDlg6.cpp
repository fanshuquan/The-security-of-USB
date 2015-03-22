// MyDlg6.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg6.h"

TCHAR m_pass[MAX_PATH];
// CMyDlg6 对话框

IMPLEMENT_DYNAMIC(CMyDlg6, CDialog)

CMyDlg6::CMyDlg6(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg6::IDD, pParent)
{

}

CMyDlg6::~CMyDlg6()
{
}

void CMyDlg6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_BtnAutorun);
	DDX_Control(pDX, IDC_EDIT1, m_OldPass);
	DDX_Control(pDX, IDC_EDIT2, m_NewPass);
}


BEGIN_MESSAGE_MAP(CMyDlg6, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlg6::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg6::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDlg6::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyDlg6 消息处理程序

BOOL CMyDlg6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMyDlg6::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
}

void CMyDlg6::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int flag=0;
	if (m_BtnAutorun.GetCheck()==1)
	{
		HKEY hKey;
		TCHAR pfilename[MAX_PATH]={0};
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_WRITE|KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)
		{
			DWORD dwRet=GetModuleFileName(NULL,pfilename,MAX_PATH);
			if(RegSetValueEx(hKey,_T("USB端口安全"),0,REG_SZ,(const BYTE*)pfilename,dwRet*sizeof(TCHAR))==ERROR_SUCCESS)
				flag=1;
		}
		RegCloseKey(hKey);
	}
	if (m_BtnAutorun.GetCheck()==0)
	{
		HKEY hKey;
		TCHAR pfilename[MAX_PATH]={0};
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_QUERY_VALUE|KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if (RegDeleteValue(hKey,_T("USB端口安全"))==ERROR_SUCCESS)
			{
				flag=2;
				RegCloseKey(hKey);
			}
		}
	}
	if (flag)
	{
		MessageBox(_T("操作成功！"));
	}
}

void CMyDlg6::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strold,strnew;
	m_OldPass.GetWindowText(strold);
	m_NewPass.GetWindowText(strnew);
	::GetPrivateProfileString(_T("Password"),_T("Old"),0,m_pass,MAX_PATH,_T(".\\login.ini"));
	if(strold==m_pass)
	{
		WritePrivateProfileString(_T("Password"),_T("Old"),strnew,_T(".\\login.ini"));
		MessageBox(_T("修改成功！"));
	}
	else
	{
		MessageBox(_T("PassWord Error!"),_T("Error"),MB_OK|MB_ICONSTOP);
	}
}
