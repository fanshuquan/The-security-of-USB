// MyStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{

}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyStatic ��Ϣ�������



void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox(_T("hao"));
	ShellExecute(m_hWnd,_T("open"),_T("help.txt"),NULL,NULL,SW_SHOW);

	CStatic::OnLButtonUp(nFlags, point);
}
