// MyDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg2.h"


// CMyDlg2 对话框

IMPLEMENT_DYNAMIC(CMyDlg2, CDialog)

CMyDlg2::CMyDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg2::IDD, pParent)
{

}

CMyDlg2::~CMyDlg2()
{
}

void CMyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listDrInfo);
}


BEGIN_MESSAGE_MAP(CMyDlg2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlg2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyDlg2 消息处理程序

BOOL CMyDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listDrInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listDrInfo.InsertColumn(0,_T("盘符"),0,150);
	m_listDrInfo.InsertColumn(1,_T("类型"),0,150);
	m_listDrInfo.InsertColumn(2,_T("总容量"),0,150);
	m_listDrInfo.InsertColumn(3,_T("剩余容量"),0,150);
	EnumDrives();
// 	for (UINT i=0;i<3;i++)
// 	{
// 		m_listDrInfo.InsertItem(i,_T("abc"));
// 	}

	return TRUE;  // return TRUE unless you set the focus to a control
}



UINT nCount;//计数器


void CMyDlg2::EnumDrives()
{
	
	CString strDrives;
	TCHAR *pBuf = NULL;
	//原则上来说 4*26+1 大小就够用了，每个盘符占用4个字符，也就是：C:\0
	TCHAR szBuf[MAX_PATH] = {0};
	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szBuf);
	if (dwRet != 0){
		nCount = dwRet/4;
		pBuf = szBuf;
		for (UINT idx = 0; idx < nCount; idx++,pBuf+=4)
		{
			//strDrives.Format(_T("%c%c%c%c"),szBuf[idx],szBuf[idx+1],szBuf[idx+2],szBuf[idx+3]);
			strDrives.Format(_T("%s"), pBuf);
			m_listDrInfo.InsertItem(idx,strDrives);
			m_listDrInfo.SetItemText(idx,1,GetDriveTypeString(strDrives));
			GetDriveSpaceInfo(idx,strDrives);
			//strDrives.AppendFormat(_T("%s%s"), pBuf, _T("\r\n"));
		}
	}
	//return strDrives;
	//MessageBox(strDrives);
	
}

CString CMyDlg2::GetDriveTypeString(CString strDrive)
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


struct strInfo
{
	CString all;
	CString part;
}strInfoDr;

void CMyDlg2::GetDriveSpaceInfo(UINT idx,CString strDrive)
{
	CString strInfo;
	ULARGE_INTEGER nFreeBytesAvailable = {0};
	ULARGE_INTEGER nTotalNumberOfBytes = {0};
	ULARGE_INTEGER nTotalNumberOfFreeBytes = {0};

	if (GetDiskFreeSpaceEx(strDrive, &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes)) {
		//单位是字节
		//strInfo.Format(_T("可用容量：%I64u Byte\r\n总容量：%I64u Byte\r\n所有可用容量：%I64u Byte"),
		//	nFreeBytesAvailable.QuadPart, nTotalNumberOfBytes.QuadPart, nTotalNumberOfFreeBytes.QuadPart);

		//单位是GB
		long double dFreeBytesAvailable = ((long double)(nFreeBytesAvailable.QuadPart))/(1024*1024*1024);
		long double dTotalNumberOfBytes = ((long double)(nTotalNumberOfBytes.QuadPart))/(1024*1024*1024);
		//long double dTotalNumberOfFreeBytes = ((long double)(nTotalNumberOfFreeBytes.QuadPart))/(1024*1024*1024);

		strInfoDr.all.Format(_T("%.2Lf GB"),dTotalNumberOfBytes);
		strInfoDr.part.Format(_T("%.2Lf GB"),dFreeBytesAvailable);
		m_listDrInfo.SetItemText(idx,2,strInfoDr.all);
		m_listDrInfo.SetItemText(idx,3,strInfoDr.part);
	}

	//return strInfoDr;
}
void CMyDlg2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(UINT idx=0;idx<nCount;idx++)
	if (_tcscmp(_T("U盘"),m_listDrInfo.GetItemText(idx,1)))
	{
		m_listDrInfo.DeleteItem(idx);
		idx--;
		nCount--;
	}
}

void CMyDlg2::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listDrInfo.DeleteAllItems();
	EnumDrives();
}
