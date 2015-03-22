// LOGIN.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "LOGIN.h"


// CLOGIN 对话框
TCHAR m_password[MAX_PATH];

IMPLEMENT_DYNAMIC(CLOGIN, CDialog)

CLOGIN::CLOGIN(CWnd* pParent /*=NULL*/)
	: CDialog(CLOGIN::IDD, pParent)
{

}

CLOGIN::~CLOGIN()
{
}

void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_pass);
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialog)
END_MESSAGE_MAP()


// CLOGIN 消息处理程序

void CLOGIN::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CString   strPass;
	::GetPrivateProfileString(_T("Password"),_T("Old"),0,m_password,MAX_PATH,_T(".\\login.ini"));
	GetDlgItemText(IDC_EDIT1,strPass);

	if(strPass==m_password)
	{
		CDialog::OnOK();
	}
	else
	{
		MessageBox("PassWord Error!","Error",MB_OK|MB_ICONSTOP);
		m_pass.SetFocus();
		m_pass.SetSel(0,-1);//文本被全选
	}


	//CDialog::OnOK();
}

BOOL CLOGIN::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT1,_T("fanshuquan"));
	//::WritePrivateProfileString(_T("Password"),_T("Old"),_T("fanshuquan"),_T(".\\login.ini"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLOGIN::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	exit(0);
	CDialog::OnCancel();
}
