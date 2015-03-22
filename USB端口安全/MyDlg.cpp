// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg.h"


// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMyDlg 消息处理程序

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&m_bmp);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE

}

HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return (HBRUSH)m_brush;
}
