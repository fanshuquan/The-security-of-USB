// MyDlg2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyDlg2.h"


// CMyDlg2 �Ի���

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


// CMyDlg2 ��Ϣ�������

BOOL CMyDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listDrInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listDrInfo.InsertColumn(0,_T("�̷�"),0,150);
	m_listDrInfo.InsertColumn(1,_T("����"),0,150);
	m_listDrInfo.InsertColumn(2,_T("������"),0,150);
	m_listDrInfo.InsertColumn(3,_T("ʣ������"),0,150);
	EnumDrives();
// 	for (UINT i=0;i<3;i++)
// 	{
// 		m_listDrInfo.InsertItem(i,_T("abc"));
// 	}

	return TRUE;  // return TRUE unless you set the focus to a control
}



UINT nCount;//������


void CMyDlg2::EnumDrives()
{
	
	CString strDrives;
	TCHAR *pBuf = NULL;
	//ԭ������˵ 4*26+1 ��С�͹����ˣ�ÿ���̷�ռ��4���ַ���Ҳ���ǣ�C:\0
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
		//��λ���ֽ�
		//strInfo.Format(_T("����������%I64u Byte\r\n��������%I64u Byte\r\n���п���������%I64u Byte"),
		//	nFreeBytesAvailable.QuadPart, nTotalNumberOfBytes.QuadPart, nTotalNumberOfFreeBytes.QuadPart);

		//��λ��GB
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(UINT idx=0;idx<nCount;idx++)
	if (_tcscmp(_T("U��"),m_listDrInfo.GetItemText(idx,1)))
	{
		m_listDrInfo.DeleteItem(idx);
		idx--;
		nCount--;
	}
}

void CMyDlg2::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listDrInfo.DeleteAllItems();
	EnumDrives();
}
