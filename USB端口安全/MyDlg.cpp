// MyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyDlg.h"


// CMyDlg �Ի���

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


// CMyDlg ��Ϣ�������

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDB_BITMAP2);
	m_brush.CreatePatternBrush(&m_bmp);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE

}

HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return (HBRUSH)m_brush;
}
