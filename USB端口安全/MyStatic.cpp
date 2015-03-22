// MyStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
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



// CMyStatic 消息处理程序



void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox(_T("hao"));
	ShellExecute(m_hWnd,_T("open"),_T("help.txt"),NULL,NULL,SW_SHOW);

	CStatic::OnLButtonUp(nFlags, point);
}
