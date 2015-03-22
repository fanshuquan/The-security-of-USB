// USB�˿ڰ�ȫDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "USB�˿ڰ�ȫDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_STATUSBARCTRL 10000
#define  MYWM_NOTIFYICON  WM_USER+2 

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUSB�˿ڰ�ȫDlg �Ի���




CUSB�˿ڰ�ȫDlg::CUSB�˿ڰ�ȫDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSB�˿ڰ�ȫDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSB�˿ڰ�ȫDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HELP, m_MyStatic);
}

BEGIN_MESSAGE_MAP(CUSB�˿ڰ�ȫDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CUSB�˿ڰ�ȫDlg::OnBnClickedCancel)
	ON_COMMAND(ID_MENU_HIDE, &CUSB�˿ڰ�ȫDlg::OnMenuHide)
	ON_COMMAND(ID_MENU_SHOW, &CUSB�˿ڰ�ȫDlg::OnMenuShow)
	ON_COMMAND(ID_MENU_EXIT, &CUSB�˿ڰ�ȫDlg::OnMenuExit)
	ON_COMMAND(ID_TOOL1, &CUSB�˿ڰ�ȫDlg::OnToolfun)
	ON_COMMAND(ID_TOOL2, &CUSB�˿ڰ�ȫDlg::OnTool1fun)
	ON_COMMAND(ID_TOOL3, &CUSB�˿ڰ�ȫDlg::OnTool2fun)
	ON_COMMAND(ID_TOOL4, &CUSB�˿ڰ�ȫDlg::OnTool3fun)
	ON_COMMAND(ID_TOOL5, &CUSB�˿ڰ�ȫDlg::OnTool4fun)
	ON_COMMAND(ID_TOOL6, &CUSB�˿ڰ�ȫDlg::OnTool5fun)
	ON_COMMAND(ID_TOOL7, &CUSB�˿ڰ�ȫDlg::OnTool6fun)
	
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUSB�˿ڰ�ȫDlg ��Ϣ�������

BOOL CUSB�˿ڰ�ȫDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	
	m_wndStatusBarCtrl.Create(CCS_BOTTOM|WS_CHILD|WS_VISIBLE|SBARS_SIZEGRIP,CRect(0,0,0,0),this,IDC_STATUSBARCTRL);
	const int nParts = 3;
	CRect rect;

	m_wndStatusBarCtrl.GetClientRect(&rect);
	int widths[nParts] = {rect.left+250,rect.left+500,-1};

	VERIFY( m_wndStatusBarCtrl.SetParts(nParts, widths) );
	SetTimer(0,1000,NULL);
	

 	m_wndStatusBarCtrl.SetText(_T(" ��ϵ��ʽ(QQ)��2460463542"),1,0);
 	m_wndStatusBarCtrl.SetText(_T("��Ϸ�ʹ�ñ������"),2,0);

	m_sIcon.cbSize=sizeof(NOTIFYICONDATA);
	m_sIcon.hWnd=GetSafeHwnd();
	m_sIcon.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_sIcon.uCallbackMessage=MYWM_NOTIFYICON;
	CString szToolTip;
	szToolTip=_T("USB�˿ڰ�ȫ");
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
	m_mydlg->SetParent(this);//���ø�����
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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUSB�˿ڰ�ȫDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUSB�˿ڰ�ȫDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CUSB�˿ڰ�ȫDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUSB�˿ڰ�ȫDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CTime t=CTime::GetCurrentTime();
	CString temp;
	temp.Format(_T(" ����ʱ����: %d��%d��%d��%d:%d:%d !"),t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	m_wndStatusBarCtrl.SetText(temp,0,0);
	CDialog::OnTimer(nIDEvent);
}



LRESULT CUSB�˿ڰ�ȫDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class

	switch(message){

	case MYWM_NOTIFYICON:       
		//������û��������Ϣ
		if(lParam==WM_LBUTTONDBLCLK)
		{  //���˫��ʱ�����ڳ���
			AfxGetApp()->m_pMainWnd->
				ShowWindow(SW_SHOW);
		}
		else if(lParam==WM_RBUTTONDOWN){ 
			//����Ҽ����������˵�
			CMenu menu;

			menu.LoadMenu(IDR_MENU1); 
			//�������ȶ���Ĳ˵�
			CMenu* pMenu=menu.GetSubMenu(0);
			CPoint pos;
			GetCursorPos(&pos);
			pMenu->TrackPopupMenu
				(TPM_LEFTALIGN|TPM_RIGHTBUTTON,
				pos.x,pos.y,AfxGetMainWnd());
		}
		break;
	case WM_SYSCOMMAND:     
		//�����ϵͳ��Ϣ
		if(wParam==SC_MINIMIZE){ 
			//���յ���С����Ϣʱ����������
			AfxGetApp()->m_pMainWnd->
				ShowWindow(SW_HIDE);
			return 0;
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}


void CUSB�˿ڰ�ȫDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CUSB�˿ڰ�ȫDlg::OnMenuHide()
{
	// TODO: �ڴ���������������
	ShowWindow(SW_HIDE);
}

void CUSB�˿ڰ�ȫDlg::OnMenuShow()
{
	// TODO: �ڴ���������������
	ShowWindow(SW_SHOW);
}

void CUSB�˿ڰ�ȫDlg::OnMenuExit()
{
	// TODO: �ڴ���������������
	::PostQuitMessage(0);
}

void CUSB�˿ڰ�ȫDlg::OnDestroy()
{
	CDialog::OnDestroy();

	::Shell_NotifyIcon(NIM_DELETE,&m_sIcon);//��ɾ������ͼ�����˳�
	// TODO: �ڴ˴������Ϣ����������
}

void CUSB�˿ڰ�ȫDlg::OnToolfun()
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
void CUSB�˿ڰ�ȫDlg::OnTool1fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->ShowWindow(SW_SHOW);
}
void CUSB�˿ڰ�ȫDlg::OnTool3fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->ShowWindow(SW_SHOW);
}
void CUSB�˿ڰ�ȫDlg::OnTool4fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->ShowWindow(SW_SHOW);
}
void CUSB�˿ڰ�ȫDlg::OnTool5fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->ShowWindow(SW_SHOW);
}
void CUSB�˿ڰ�ȫDlg::OnTool6fun()
{
	CMyDlg6 dlg;
	dlg.DoModal();
}
void CUSB�˿ڰ�ȫDlg::OnTool2fun()
{
	m_mydlg->SendMessage(WM_CLOSE,0,0);
	m_mydlg2->SendMessage(WM_CLOSE,0,0);
	m_mydlg3->SendMessage(WM_CLOSE,0,0);
	m_mydlg4->SendMessage(WM_CLOSE,0,0);
	m_mydlg5->SendMessage(WM_CLOSE,0,0);
//	m_mydlg6->SendMessage(WM_CLOSE,0,0);
	m_mydlg7->ShowWindow(SW_SHOW);
}