// MyDlg6.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyDlg6.h"

TCHAR m_pass[MAX_PATH];
// CMyDlg6 �Ի���

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


// CMyDlg6 ��Ϣ�������

BOOL CMyDlg6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMyDlg6::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC_SHOW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
}

void CMyDlg6::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int flag=0;
	if (m_BtnAutorun.GetCheck()==1)
	{
		HKEY hKey;
		TCHAR pfilename[MAX_PATH]={0};
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_WRITE|KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)
		{
			DWORD dwRet=GetModuleFileName(NULL,pfilename,MAX_PATH);
			if(RegSetValueEx(hKey,_T("USB�˿ڰ�ȫ"),0,REG_SZ,(const BYTE*)pfilename,dwRet*sizeof(TCHAR))==ERROR_SUCCESS)
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
			if (RegDeleteValue(hKey,_T("USB�˿ڰ�ȫ"))==ERROR_SUCCESS)
			{
				flag=2;
				RegCloseKey(hKey);
			}
		}
	}
	if (flag)
	{
		MessageBox(_T("�����ɹ���"));
	}
}

void CMyDlg6::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strold,strnew;
	m_OldPass.GetWindowText(strold);
	m_NewPass.GetWindowText(strnew);
	::GetPrivateProfileString(_T("Password"),_T("Old"),0,m_pass,MAX_PATH,_T(".\\login.ini"));
	if(strold==m_pass)
	{
		WritePrivateProfileString(_T("Password"),_T("Old"),strnew,_T(".\\login.ini"));
		MessageBox(_T("�޸ĳɹ���"));
	}
	else
	{
		MessageBox(_T("PassWord Error!"),_T("Error"),MB_OK|MB_ICONSTOP);
	}
}
