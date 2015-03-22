// CHOOSE.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "CHOOSE.h"


// CCHOOSE 对话框

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
// CCHOOSE 消息处理程序

void CCHOOSE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , _T("All Files (*.*)|*.*||"));
	if ( fileDlg.DoModal() == IDOK ){		
		strpath=fileDlg.GetPathName();
		strfile=fileDlg.GetFileName();
		SetDlgItemText(IDC_EDIT1,strpath);
	}
}
