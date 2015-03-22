// MyDlg7.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg7.h"
#include "Dbt.h"

// CMyDlg7 对话框

IMPLEMENT_DYNAMIC(CMyDlg7, CDialog)

CMyDlg7::CMyDlg7(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg7::IDD, pParent)
{

}

CMyDlg7::~CMyDlg7()
{
}

void CMyDlg7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_LiProgress);
}


BEGIN_MESSAGE_MAP(CMyDlg7, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlg7::OnBnClickedButton2)
//	ON_WM_TIMER()
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg7::OnBnClickedButton1)	
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CMyDlg7::OnNMRclickList2)
	ON_COMMAND(ID_M_REFRESH_LIST, &CMyDlg7::OnMRefreshList)
	ON_COMMAND(ID_M_EDN_TASK, &CMyDlg7::OnMEdnTask)
	ON_COMMAND(ID_M_FIND_EXE, &CMyDlg7::OnMFindExe)
	ON_COMMAND(ID_M_COPY_PATH, &CMyDlg7::OnMCopyPath)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyDlg7::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDlg7::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyDlg7::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMyDlg7 消息处理程序

void CMyDlg7::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListBox.ResetContent();
	//KillTimer(1);
}

// void CMyDlg7::EnumDrives()
// {
// 	UINT nCount;//计数器
// 
// 	CString strDrives;
// 	TCHAR *pBuf = NULL;
// 	//原则上来说 4*26+1 大小就够用了，每个盘符占用4个字符，也就是：C:\0
// 	TCHAR szBuf[MAX_PATH] = {0};
// 	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
// 	if (dwRet != 0){
// 		nCount = dwRet/4;
// 		pBuf = szBuf;
// 		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
// 		{
// 			strDrives.Format(_T("%s"), pBuf);
// 			if (GetDriveTypeString(strDrives)==_T("U盘"))
// 			{
// 				CString str;
// 				str.Format(_T("找到移动设备，开始扫描 %s ..."),strDrives);
// 				m_ListBox.AddString(str);
// 				SetTimer(1,100,NULL);
// 			}
// // 			m_listDrInfo.SetItemText(idx,1,GetDriveTypeString(strDrives));
// // 			GetDriveSpaceInfo(idx,strDrives);
// 			//strDrives.AppendFormat(_T("%s%s"), pBuf, _T("\r\n"));
// 		}
// 	}
// }


CString CMyDlg7::GetDriveTypeString(CString strDrive)
{
	//传递的参数至少要包含：盘符+ :
	//也可以是目录的路径，但是结尾必须有\\符号
	CString strDriveTpye;
	UINT uType = GetDriveType(strDrive);
	switch (uType)
	{
	case DRIVE_UNKNOWN:
		strDriveTpye = _T("类型未知！");
		break;
	case DRIVE_NO_ROOT_DIR:
		strDriveTpye = _T("指定的盘符不存在！");
		break;
	case DRIVE_REMOVABLE:
		strDriveTpye = _T("U盘");
		break;
	case DRIVE_FIXED:
		strDriveTpye = _T("硬盘");
		break;
	case DRIVE_REMOTE:
		strDriveTpye = _T("网络磁盘");
		break;
	case DRIVE_CDROM:
		strDriveTpye = _T("CD-ROM");
		break;
	case DRIVE_RAMDISK:
		strDriveTpye = _T("RAM磁盘");
		break;
	default:
		break;
	}
	return strDriveTpye;
}

static const GUID GUID_DEVINTERFACE_LIST[] = 
	{
		// GUID_DEVINTERFACE_USB_DEVICE
		{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

// 		// GUID_DEVINTERFACE_DISK
// 		{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
// 
// 		// GUID_DEVINTERFACE_HID, 
// 		{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
// 
// 		// GUID_NDIS_LAN_CLASS
// 		{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

	};
BOOL CMyDlg7::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_ListBox.AddString(_T("abc"));

	HDEVNOTIFY hDevNotify;
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	for(int i=0; i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID); i++) 
	{
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
		hDevNotify = RegisterDeviceNotification(this->GetSafeHwnd(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
		if( !hDevNotify ) 
		{
			return FALSE;
		}
	}

	m_LiProgress.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_LiProgress.InsertColumn(0,_T("进程名称"),0,100);
	m_LiProgress.InsertColumn(1,_T("ID"),0,80);
	m_LiProgress.InsertColumn(2,_T("文件路径"),0,200);

	AdjustPrivileges();
	GetProcessList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMyDlg7::FindAutorun(TCHAR strDrive)
{
	CString str;
	HANDLE hFile;
	int i,j,n;
	DWORD dwRead;
	TCHAR buff[MAX_PATH];
	TCHAR name[MAX_PATH]=_T("H:\\");
	TCHAR sname[MAX_PATH]=_T("H:\\autorun.inf");
	name[0]=strDrive;
	sname[0]=name[0];
	SetFileAttributes(sname,FILE_ATTRIBUTE_NORMAL);
	hFile=CreateFile(sname,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
	ReadFile(hFile,&buff,strlen(buff)*sizeof(TCHAR),&dwRead,NULL);
	CloseHandle(hFile);

	if (DeleteFile(sname))
	{
		m_ListBox.InsertString(m_ListBox.GetCount(),_T("autorun文件已被删除！"));
	}
	for (i=0;buff[i]>=1&&buff[i]<=MAX_PATH;i++)//读取文件内容
	{
		if ((buff[i-3]=='e')&&(buff[i-2]=='x')&&(buff[i-1]=='e'))
		{
			buff[i]=0;
			break;
		}
	}
	n=i;
	while(buff[n]!='='&&(n>9)) n-=1;
	for (i=n+1,j=3;buff[i];i++,j++)
	{
		name[j]=buff[i];
	}
	name[j]=0;
	SetFileAttributes(name,FILE_ATTRIBUTE_NORMAL);
	//处理程序。。。
	if (DeleteFile(name))
	{
		m_ListBox.InsertString(m_ListBox.GetCount(),_T("autorun所指向的可执行文件已被删除！"));
	}
	else
	m_ListBox.InsertString(m_ListBox.GetCount(),_T("无autorun病毒！"));
	m_ListBox.InsertString(m_ListBox.GetCount(),_T("此盘扫描完成！"));
}


// void CMyDlg7::OnTimer(UINT_PTR nIDEvent)
// {
// // TODO: 在此添加消息处理程序代码和/或调用默认值
// // 	static int count=0;
// // 	CString str;
// // 	str.Format(_T("%d"),count);
// // 	m_ListBox.AddString(str);
// // 	count++;
// //	FindAutorun(cha);
// 
// 	CDialog::OnTimer(nIDEvent);
// }

TCHAR cha;
void CMyDlg7::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	dosomething();
}

BOOL CMyDlg7::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	m_ListBox.ResetContent();
	DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	//这里进行信息匹配,比如guid等
	//针对各个事件进行处理.
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE:
		{
			int x=MessageBox(_T("移除移动设备！"));
			if(x==IDOK)
				dosomething();
			break;
		}
	case DBT_DEVICEARRIVAL:
		//FindAutorun();
		{
			int x=MessageBox(_T("检测到移动设备！"));
			if(x==IDOK)
			dosomething();
			break;
		}
	default:
		break;
	}
	return TRUE;
}


void CMyDlg7::dosomething()
{
	//EnumDrives();
	m_ListBox.ResetContent();

	UINT nCount;//计数器

	CString strDrives;
	TCHAR *pBuf = NULL;
	//原则上来说 4*26+1 大小就够用了，每个盘符占用4个字符，也就是：C:\0
	TCHAR szBuf[MAX_PATH] = {0};
	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
	if (dwRet != 0)
	{
		nCount = dwRet/4;
		pBuf = szBuf;
		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
		{

			strDrives.Format(_T("%s"), pBuf);
			if (_tcscmp(GetDriveTypeString(strDrives),_T("U盘"))==0)
			{
				cha=pBuf[0];
				CString str;
				str.Format(_T("找到移动设备，开始扫描 %s ..."),strDrives);
				m_ListBox.InsertString(m_ListBox.GetCount(),str);
				//SetTimer(1,100,NULL);
				FindAutorun(pBuf[0]);
			}
			//m_listDrInfo.SetItemText(idx,1,GetDriveTypeString(strDrives));
			//GetDriveSpaceInfo(idx,strDrives);
			//strDrives.AppendFormat(_T("%s%s"), pBuf, _T("\r\n"));
		}
	}
}


BOOL CMyDlg7::GetProcessList()
{
	BOOL bResult = FALSE;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if ( hSnap == INVALID_HANDLE_VALUE )
		return FALSE;

	int idx = 0;
	CString strID;
	HANDLE hProcess = NULL;
	PROCESSENTRY32 info = {0};
	info.dwSize = sizeof(PROCESSENTRY32);

	BOOL bRet = Process32First(hSnap, &info);
	while(bRet) {
		idx = m_LiProgress.InsertItem(m_LiProgress.GetItemCount(), _T(""));
		m_LiProgress.SetItemText(idx, 0, info.szExeFile);
		strID.Empty();
		strID.Format(_T("%d"), info.th32ProcessID);
		m_LiProgress.SetItemText(idx, 1, strID);

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, info.th32ProcessID);
		if (hProcess) {
			TCHAR szPath[MAX_PATH] = {0};
			GetModuleFileNameEx(hProcess, NULL, szPath, MAX_PATH);
			m_LiProgress.SetItemText(idx, 2, szPath);
		}
		bRet = Process32Next(hSnap, &info);
	}
	return TRUE;
}

BOOL CMyDlg7::AdjustPrivileges()
{
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tp = {0};
	TOKEN_PRIVILEGES oldtp = {0};
	DWORD dwSize = sizeof(TOKEN_PRIVILEGES);
	LUID luid = {0};

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		if (GetLastError()==ERROR_CALL_NOT_IMPLEMENTED)
			return TRUE;
		else
			return FALSE;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
		CloseHandle(hToken);
		return FALSE;
	}

	tp.PrivilegeCount=1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	/* Adjust Token Privileges */
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), &oldtp, &dwSize)) {
		CloseHandle(hToken);
		return FALSE;
	}

	// close handles
	CloseHandle(hToken);
	return TRUE;
}
void CMyDlg7::OnNMRclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if ( pNMItemActivate->iItem < 0 ) return;

	CString strID = m_LiProgress.GetItemText(pNMItemActivate->iItem, 1);

	CPoint pt;
	GetCursorPos(&pt);
	CMenu mMenu, *pMenu;
	mMenu.LoadMenu(IDR_MENU2);
	pMenu = mMenu.GetSubMenu(0);
	if (strID == _T("0") || strID == _T("4")){
		pMenu->EnableMenuItem(ID_M_EDN_TASK, MF_BYCOMMAND|MF_GRAYED);
		pMenu->EnableMenuItem(ID_M_FIND_EXE, MF_BYCOMMAND|MF_GRAYED);
		pMenu->EnableMenuItem(ID_M_COPY_PATH, MF_BYCOMMAND|MF_GRAYED);
	}
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	*pResult = 0;
}

void CMyDlg7::OnMRefreshList()
{
	// TODO: 在此添加命令处理程序代码

	m_LiProgress.DeleteAllItems();
	GetProcessList();
}

void CMyDlg7::OnMEdnTask()
{
	// TODO: 在此添加命令处理程序代码
	int idx =m_LiProgress.GetSelectionMark();
	CString strID = m_LiProgress.GetItemText(idx, 1);
	CString strName = m_LiProgress.GetItemText(idx, 0);

	int iRet = MessageBox(_T("您确定要结束 ")+strName+_T(" 吗？"), _T("友情提示"), MB_OKCANCEL);
	if (iRet == IDCANCEL) return;

	if ( strID == _T("0") || strName == _T("4")) { //实际上这个位置的判断是多余的
		MessageBox(_T("系统进程，无法结束！"), _T("提示"));
	}else{
		BOOL bRet = FALSE;
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE|PROCESS_QUERY_INFORMATION, FALSE, _tstoi(strID));
		if ( hProcess != NULL ) {
			bRet = TerminateProcess(hProcess, -1);
			CloseHandle(hProcess);
		}

		if ( !bRet ) {
			MessageBox(_T("结束进程 \" ") + strName + _T(" \" 失败，请重试！"), _T("提示"));
		}else{
			m_LiProgress.DeleteItem(idx);
		}
	}
}

void CMyDlg7::OnMFindExe()
{
	// TODO: 在此添加命令处理程序代码
	int idx = m_LiProgress.GetSelectionMark();
	CString strPath = m_LiProgress.GetItemText(idx, 2);
	if (strPath.GetLength() > 0)
		ShellExecute(m_hWnd, _T("open"), _T("Explorer.exe"), _T("/select,")+strPath, NULL, SW_SHOW);
}

void CMyDlg7::OnMCopyPath()
{
	// TODO: 在此添加命令处理程序代码
	int idx = m_LiProgress.GetSelectionMark();
	CString strPath = m_LiProgress.GetItemText(idx, 2);

	if (!OpenClipboard()) return;
	if(!EmptyClipboard()) {
		CloseClipboard();
		return;
	}

	size_t cbStr = (strPath.GetLength()+1)*sizeof(TCHAR);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
	memcpy_s(GlobalLock(hData), cbStr, strPath.LockBuffer(), cbStr);
	GlobalUnlock(hData);
	strPath.UnlockBuffer();

	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
	if (::SetClipboardData(uiFormat, hData) == NULL) {
		MessageBox(_T("设置剪贴板数据失败！"));
		CloseClipboard();
		return;
	}
	CloseClipboard();
}


void CMyDlg7::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LiProgress.DeleteAllItems();
	GetProcessList();
}

void CMyDlg7::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代
	//m_LiProgress.DeleteAllItems();
// 	MessageBox(_T("a"));
// 	m_ListBox.ResetContent();
// 
// 	UINT nCount;//计数器
// 
// 	CString strDrives;
// 	TCHAR *pBuf = NULL;
// 	//原则上来说 4*26+1 大小就够用了，每个盘符占用4个字符，也就是：C:\0
// 	TCHAR szBuf[MAX_PATH] = {0};
// 	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
// 	if (dwRet != 0)
// 	{
// 		nCount = dwRet/4;
// 		pBuf = szBuf;
// 		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
// 		{
// 
// 			strDrives.Format(_T("%s"), pBuf);
// 			if (_tcscmp(GetDriveTypeString(strDrives),_T("U盘"))==0)
// 			{
// 				cha=pBuf[0];
// 				int coun=m_LiProgress.GetItemCount();
// 				//CString str;
// 				for(UINT id=0;id< coun;id++)
// 				{
// 					CString str;
// 					str=m_LiProgress.GetItemText(id,2);
// 					if (str.GetAt(0)!=strDrives.GetAt(0))
// 					{
// 						m_LiProgress.DeleteItem(id);
// 						id--;
// 						coun--;
// 					}
// 				}
// 				//str.Format(_T("找到移动设备，开始扫描 %s ..."),strDrives);
// 				//m_ListBox.InsertString(m_ListBox.GetCount(),str);
// 				//SetTimer(1,100,NULL);
// 				//FindAutorun(pBuf[0]);
// 			}
// 			//m_listDrInfo.SetItemText(idx,1,GetDriveTypeString(strDrives));
// 			//GetDriveSpaceInfo(idx,strDrives);
// 			//strDrives.AppendFormat(_T("%s%s"), pBuf, _T("\r\n"));
// 		}
// 	}
	///////////////////////////////////////////////////////////////////////
	CCHOOSE *chDlg;
	chDlg=new CCHOOSE((CWnd*)this);
	INT_PTR iRet=chDlg->DoModal();
	if (iRet==IDOK)
	{
		TCHAR szFilePath[MAX_PATH]; 
		CString szp;
		if(GetModuleFileName(NULL,szFilePath,MAX_PATH)> 0) 
		{ 
			(*strrchr(szFilePath, '\\'))= '\0';//丢掉文件名，得到路径 
		}
		//MessageBox(szFilePath);
		
		loginpath.Format(_T("%s\\login.ini"),szFilePath);
		//MessageBox(loginpath);
		WritePrivateProfileString(_T("path"),_T("p"),strpath,loginpath);
		WritePrivateProfileString(_T("path"),_T("f"),strfile,loginpath);
		//WritePrivateProfileString(_T("path"),_T("l"),loginpath,loginpath);
	}
	///////////////////////////////////////////////////////////////////////
}
void CMyDlg7::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(strfile);
	CString cstr;
	TCHAR fil[MAX_PATH];
	TCHAR pat[MAX_PATH];
	//TCHAR log[MAX_PATH];
	//GetPrivateProfileString(_T("path"),_T("f"),0,log,MAX_PATH,loginpath);
	GetPrivateProfileString(_T("path"),_T("p"),0,pat,MAX_PATH,_T(".\\login.ini"));
	GetPrivateProfileString(_T("path"),_T("f"),0,fil,MAX_PATH,_T(".\\login.ini"));
	//MessageBox(loginpath);
	ShellExecute(m_hWnd,_T("open"),pat,NULL,NULL,SW_SHOWNORMAL);
}