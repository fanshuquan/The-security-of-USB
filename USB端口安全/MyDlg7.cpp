// MyDlg7.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyDlg7.h"
#include "Dbt.h"

// CMyDlg7 �Ի���

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


// CMyDlg7 ��Ϣ�������

void CMyDlg7::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListBox.ResetContent();
	//KillTimer(1);
}

// void CMyDlg7::EnumDrives()
// {
// 	UINT nCount;//������
// 
// 	CString strDrives;
// 	TCHAR *pBuf = NULL;
// 	//ԭ������˵ 4*26+1 ��С�͹����ˣ�ÿ���̷�ռ��4���ַ���Ҳ���ǣ�C:\0
// 	TCHAR szBuf[MAX_PATH] = {0};
// 	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
// 	if (dwRet != 0){
// 		nCount = dwRet/4;
// 		pBuf = szBuf;
// 		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
// 		{
// 			strDrives.Format(_T("%s"), pBuf);
// 			if (GetDriveTypeString(strDrives)==_T("U��"))
// 			{
// 				CString str;
// 				str.Format(_T("�ҵ��ƶ��豸����ʼɨ�� %s ..."),strDrives);
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
	//���ݵĲ�������Ҫ�������̷�+ :
	//Ҳ������Ŀ¼��·�������ǽ�β������\\����
	CString strDriveTpye;
	UINT uType = GetDriveType(strDrive);
	switch (uType)
	{
	case DRIVE_UNKNOWN:
		strDriveTpye = _T("����δ֪��");
		break;
	case DRIVE_NO_ROOT_DIR:
		strDriveTpye = _T("ָ�����̷������ڣ�");
		break;
	case DRIVE_REMOVABLE:
		strDriveTpye = _T("U��");
		break;
	case DRIVE_FIXED:
		strDriveTpye = _T("Ӳ��");
		break;
	case DRIVE_REMOTE:
		strDriveTpye = _T("�������");
		break;
	case DRIVE_CDROM:
		strDriveTpye = _T("CD-ROM");
		break;
	case DRIVE_RAMDISK:
		strDriveTpye = _T("RAM����");
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	m_LiProgress.InsertColumn(0,_T("��������"),0,100);
	m_LiProgress.InsertColumn(1,_T("ID"),0,80);
	m_LiProgress.InsertColumn(2,_T("�ļ�·��"),0,200);

	AdjustPrivileges();
	GetProcessList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
		m_ListBox.InsertString(m_ListBox.GetCount(),_T("autorun�ļ��ѱ�ɾ����"));
	}
	for (i=0;buff[i]>=1&&buff[i]<=MAX_PATH;i++)//��ȡ�ļ�����
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
	//������򡣡���
	if (DeleteFile(name))
	{
		m_ListBox.InsertString(m_ListBox.GetCount(),_T("autorun��ָ��Ŀ�ִ���ļ��ѱ�ɾ����"));
	}
	else
	m_ListBox.InsertString(m_ListBox.GetCount(),_T("��autorun������"));
	m_ListBox.InsertString(m_ListBox.GetCount(),_T("����ɨ����ɣ�"));
}


// void CMyDlg7::OnTimer(UINT_PTR nIDEvent)
// {
// // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	dosomething();
}

BOOL CMyDlg7::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	m_ListBox.ResetContent();
	DEV_BROADCAST_DEVICEINTERFACE* dbd = (DEV_BROADCAST_DEVICEINTERFACE*) dwData;
	//���������Ϣƥ��,����guid��
	//��Ը����¼����д���.
	switch (nEventType)
	{
	case DBT_DEVICEREMOVECOMPLETE:
		{
			int x=MessageBox(_T("�Ƴ��ƶ��豸��"));
			if(x==IDOK)
				dosomething();
			break;
		}
	case DBT_DEVICEARRIVAL:
		//FindAutorun();
		{
			int x=MessageBox(_T("��⵽�ƶ��豸��"));
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

	UINT nCount;//������

	CString strDrives;
	TCHAR *pBuf = NULL;
	//ԭ������˵ 4*26+1 ��С�͹����ˣ�ÿ���̷�ռ��4���ַ���Ҳ���ǣ�C:\0
	TCHAR szBuf[MAX_PATH] = {0};
	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
	if (dwRet != 0)
	{
		nCount = dwRet/4;
		pBuf = szBuf;
		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
		{

			strDrives.Format(_T("%s"), pBuf);
			if (_tcscmp(GetDriveTypeString(strDrives),_T("U��"))==0)
			{
				cha=pBuf[0];
				CString str;
				str.Format(_T("�ҵ��ƶ��豸����ʼɨ�� %s ..."),strDrives);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���������������

	m_LiProgress.DeleteAllItems();
	GetProcessList();
}

void CMyDlg7::OnMEdnTask()
{
	// TODO: �ڴ���������������
	int idx =m_LiProgress.GetSelectionMark();
	CString strID = m_LiProgress.GetItemText(idx, 1);
	CString strName = m_LiProgress.GetItemText(idx, 0);

	int iRet = MessageBox(_T("��ȷ��Ҫ���� ")+strName+_T(" ��"), _T("������ʾ"), MB_OKCANCEL);
	if (iRet == IDCANCEL) return;

	if ( strID == _T("0") || strName == _T("4")) { //ʵ�������λ�õ��ж��Ƕ����
		MessageBox(_T("ϵͳ���̣��޷�������"), _T("��ʾ"));
	}else{
		BOOL bRet = FALSE;
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE|PROCESS_QUERY_INFORMATION, FALSE, _tstoi(strID));
		if ( hProcess != NULL ) {
			bRet = TerminateProcess(hProcess, -1);
			CloseHandle(hProcess);
		}

		if ( !bRet ) {
			MessageBox(_T("�������� \" ") + strName + _T(" \" ʧ�ܣ������ԣ�"), _T("��ʾ"));
		}else{
			m_LiProgress.DeleteItem(idx);
		}
	}
}

void CMyDlg7::OnMFindExe()
{
	// TODO: �ڴ���������������
	int idx = m_LiProgress.GetSelectionMark();
	CString strPath = m_LiProgress.GetItemText(idx, 2);
	if (strPath.GetLength() > 0)
		ShellExecute(m_hWnd, _T("open"), _T("Explorer.exe"), _T("/select,")+strPath, NULL, SW_SHOW);
}

void CMyDlg7::OnMCopyPath()
{
	// TODO: �ڴ���������������
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
		MessageBox(_T("���ü���������ʧ�ܣ�"));
		CloseClipboard();
		return;
	}
	CloseClipboard();
}


void CMyDlg7::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LiProgress.DeleteAllItems();
	GetProcessList();
}

void CMyDlg7::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ��������
	//m_LiProgress.DeleteAllItems();
// 	MessageBox(_T("a"));
// 	m_ListBox.ResetContent();
// 
// 	UINT nCount;//������
// 
// 	CString strDrives;
// 	TCHAR *pBuf = NULL;
// 	//ԭ������˵ 4*26+1 ��С�͹����ˣ�ÿ���̷�ռ��4���ַ���Ҳ���ǣ�C:\0
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
// 			if (_tcscmp(GetDriveTypeString(strDrives),_T("U��"))==0)
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
// 				//str.Format(_T("�ҵ��ƶ��豸����ʼɨ�� %s ..."),strDrives);
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
			(*strrchr(szFilePath, '\\'))= '\0';//�����ļ������õ�·�� 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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