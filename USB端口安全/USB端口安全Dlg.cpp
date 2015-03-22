// USB端口安全Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "USB端口安全Dlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_STATUSBARCTRL 10000
#define  MYWM_NOTIFYICON  WM_USER+2 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUSB端口安全Dlg 对话框




CUSB端口安全Dlg::CUSB端口安全Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSB端口安全Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSB端口安全Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HELP, m_MyStatic);
}

BEGIN_MESSAGE_MAP(CUSB端口安全Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CUSB端口安全Dlg::OnBnClickedCancel)
	ON_COMMAND(ID_MENU_HIDE, &CUSB端口安全Dlg::OnMenuHide)
	ON_COMMAND(ID_MENU_SHOW, &CUSB端口安全Dlg::OnMenuShow)
	ON_COMMAND(ID_MENU_EXIT, &CUSB端口安全Dlg::OnMenuExit)
	ON_COMMAND(ID_TOOL1, &CUSB端口安全Dlg::OnToolfun)
	ON_COMMAND(ID_TOOL2, &CUSB端口安全Dlg::OnTool1fun)
	ON_COMMAND(ID_TOOL3, &CUSB端口安全Dlg::OnTool2fun)
	ON_COMMAND(ID_TOOL4, &CUSB端口安全Dlg::OnTool3fun)
	ON_COMMAND(ID_TOOL5, &CUSB端口安全Dlg::OnTool4fun)
	ON_COMMAND(ID_TOOL6, &CUSB端口安全Dlg::OnTool5fun)
	ON_COMMAND(ID_TOOL7, &CUSB端口安全Dlg::OnTool6fun)
	
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUSB端口安全Dlg 消息处理程序

BOOL CUSB端口安全Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	m_wndStatusBarCtrl.Create(CCS_BOTTOM|WS_CHILD|WS_VISIBLE|SBARS_SIZEGRIP,CRect(0,0,0,0),this,IDC_STATUSBARCTRL);
	const int nParts = 3;
	CRect rect;

	m_wndStatusBarCtrl.GetClientRect(&rect);
	int widths[nParts] = {rect.left+250,rect.left+500,-1};

	VERIFY( m_wndStatusBarCtrl.SetParts(nParts, widths) );
	SetTimer(0,1000,NULL);
	

 	m_wndStatusBarCtrl.SetText(_T(" 联系方式(QQ)：2460463542"),1,0);
 	m_wndStatusBarCtrl.SetText(_T("请合法使用本软件！"),2,0);

	m_sIcon.cbSize=sizeof(NOTIFYICONDATA);
	m_sIcon.hWnd=GetSafeHwnd();
	m_sIcon.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_sIcon.uCallbackMessage=MYWM_NOTIFYICON;
	CString szToolTip;
	szToolTip=_T("USB端口安全");
	_tcscpy_s(m_sIcon.szTip,szToolTip);
	m_sIcon.uID=IDI_ICON1;
	HICON hIcon;
	hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_sIcon.hIcon=hIcon;
	::Shell_NotifyIcon(NIM_ADD,&m_sIcon);
	if(hIcon) ::DestroyIcon(hIcon);

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.LoadTrueColorToolBar(78,IDB_BITMAP1);
	for (int i=0;i<m_wndToolBar.GetCount();i++)
	{
		CString str;
		int idx=m_wndToolBar.GetItemID(i);
		str.LoadString(idx);
		VERIFY(m_wndToolBar.SetButtonText(i,str));
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	m_mydlg = new CMyDlg(this);
	m_mydlg->Create(IDD_DIALOG1);
	m_mydlg->SetParent(this);//设置父窗口
	GetWindowRect(&rec);
	//ScreenToClient(&rec);
	m_mydlg->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);
	m_mydlg->ShowWindow(SW_SHOW);

	m_mydlg2 = new CMyDlg2(this);
	m_mydlg2->Create(IDD_DIALOG2);
	m_mydlg2->SetParent(this);
	m_mydlg2->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

	m_mydlg3 = new CMyDlg3(this);
	m_mydlg3->Create(IDD_DIALOG3);
	m_mydlg3->SetParent(this);
	m_mydlg3->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

	m_mydlg4 = new CMyDlg4(this);
	m_mydlg4->Create(IDD_DIALOG4);
	m_mydlg4->SetParent(this);
	m_mydlg4->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

	m_mydlg5 = new CMyDlg5(this);
	m_mydlg5->Create(IDD_DIALOG5);
	m_mydlg5->SetParent(this);
	m_mydlg5->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

// 	m_mydlg6 = new CMyDlg6(this);
// 	m_mydlg6->Create(IDD_DIALOG6);
//  	m_mydlg6->SetParent(this);
//  	m_mydlg6->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

	m_mydlg7 = new CMyDlg7(this);
	m_mydlg7->Create(IDD_DIALOG7);
	m_mydlg7->SetParent(this);
	m_mydlg7->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);

// 	CLOGIN dlgg;
// 	dlgg.DoModal();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUSB端口安全Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUSB端口安全Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CUSB端口安全Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUSB端口安全Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CTime t=CTime::GetCurrentTime();
	CString temp;
	temp.Format(_T(" 现在时间是: %d年%d月%d日%d:%d:%d !"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	m_wndStatusBarCtrl.SetText(temp,0,0);
	CDialog::OnTimer(nIDEvent);
}



LRESULT CUSB端口安全Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch(message){

	case MYWM_NOTIFYICON:       
		//如果是用户定义的消息
		if(lParam==WM_LBUTTONDBLCLK)
		{  //鼠标双击时主窗口出现
			AfxGetApp()->m_pMainWnd->
				ShowWindow(SW_SHOW);
		}
		else if(lParam==WM_RBUTTONDOWN){ 
			//鼠标右键单击弹出菜单
			CMenu menu;

			menu.LoadMenu(IDR_MENU1); 
			//载入事先定义的菜单
			CMenu* pMenu=menu.GetSubMenu(0);
			CPoint pos;
			GetCursorPos(&pos);
			pMenu->TrackPopupMenu
				(TPM_LEFTALIGN|TPM_RIGHTBUTTON,
				pos.x,pos.y,AfxGetMainWnd());
		}
		break;
	case WM_SYSCOMMAND:     
		//如果是系统消息
		if(wParam==SC_MINIMIZE){ 
			//接收到最小化消息时主窗口隐藏
			AfxGetApp()->m_pMainWnd->
				ShowWindow(SW_HIDE);
			return 0;
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}


void CUSB端口安全Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CUSB端口安全Dlg::OnMenuHide()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_HIDE);
}

void CUSB端口安全Dlg::OnMenuShow()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_SHOW);
}

void CUSB端口安全Dlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	::PostQuitMessage(0);
}

void CUSB端口安全Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	::Shell_NotifyIcon(NIM_DELETE,&m_sIcon);//先删除托盘图标再退出
	// TODO: 在此处添加消息处理程序代码
}

void CUSB端口安全Dlg::OnToolfun()
{
	//m_mydlg->MoveWindow(rec.left,rec.top+100,rec.Width(),rec.Height(),TRUE);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg->ShowWindow(SW_SHOW);
}
void CUSB端口安全Dlg::OnTool1fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->ShowWindow(SW_SHOW);
}
void CUSB端口安全Dlg::OnTool3fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->ShowWindow(SW_SHOW);
}
void CUSB端口安全Dlg::OnTool4fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->ShowWindow(SW_SHOW);
}
void CUSB端口安全Dlg::OnTool5fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->ShowWindow(SW_SHOW);
}
void CUSB端口安全Dlg::OnTool6fun()
{
	CMyDlg6 dlg;
	dlg.DoModal();
}
void CUSB端口安全Dlg::OnTool2fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->ShowWindow(SW_SHOW);
}