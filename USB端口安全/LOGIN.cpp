// LOGIN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "LOGIN.h"


// CLOGIN �Ի���
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


// CLOGIN ��Ϣ�������

void CLOGIN::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
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
		m_pass.SetSel(0,-1);//�ı���ȫѡ
	}


	//CDialog::OnOK();
}

BOOL CLOGIN::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT1,_T("fanshuquan"));
	//::WritePrivateProfileString(_T("Password"),_T("Old"),_T("fanshuquan"),_T(".\\login.ini"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLOGIN::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	exit(0);
	CDialog::OnCancel();
}
