// CHOOSE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "CHOOSE.h"


// CCHOOSE �Ի���

IMPLEMENT_DYNAMIC(CCHOOSE, CDialog)

CCHOOSE::CCHOOSE(CWnd* pParent /*=NULL*/)
	: CDialog(CCHOOSE::IDD, pParent)
{

}

CCHOOSE::~CCHOOSE()
{
}

void CCHOOSE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCHOOSE, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CCHOOSE::OnBnClickedButton1)
END_MESSAGE_MAP()

CString strpath;
CString strfile;
// CCHOOSE ��Ϣ�������

void CCHOOSE::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , _T("All Files (*.*)|*.*||"));
	if ( fileDlg.DoModal() == IDOK ){		
		strpath=fileDlg.GetPathName();
		strfile=fileDlg.GetFileName();
		SetDlgItemText(IDC_EDIT1,strpath);
	}
}
