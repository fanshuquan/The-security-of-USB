// MyDlg4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USB�˿ڰ�ȫ.h"
#include "MyDlg4.h"


// CMyDlg4 �Ի���

IMPLEMENT_DYNAMIC(CMyDlg4, CDialog)

CMyDlg4::CMyDlg4(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg4::IDD, pParent)
{

}

CMyDlg4::~CMyDlg4()
{
}

void CMyDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_Btn1);
	DDX_Control(pDX, IDC_CHECK2, m_Btn2);
	DDX_Control(pDX, IDC_CHECK3, m_Btn3);
	DDX_Control(pDX, IDC_STATIC_PS, m_ps);
}


BEGIN_MESSAGE_MAP(CMyDlg4, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlg4::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_PS, &CMyDlg4::OnStnClickedStaticPs)
	ON_STN_CLICKED(IDC_STATIC_NO, &CMyDlg4::OnStnClickedStaticNo)
END_MESSAGE_MAP()


// CMyDlg4 ��Ϣ�������

BOOL CMyDlg4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	static CFont font;   //���徲̬����
	font.CreatePointFont(140, "����");
	GetDlgItem(IDC_STATIC_FONT)->SetFont(&font);

	CBrush m_brush;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMyDlg4::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/////////////////////////////////�ر�USB�洢�豸���̷��Զ�����/////////////////////////////////////////
	HKEY hKey;
	DWORD szValue;
	CString flag;
	if (m_Btn1.GetCheck()==1)
	{
		szValue=4;
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Services\\USBSTOR"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("Start"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag=_T("�ѹر�USB�洢�豸���̷��Զ�����\r\n");
			else flag=_T("");
		}		
		RegCloseKey(hKey);
		
	}
	if (m_Btn1.GetCheck()==0)
	{
		szValue=3;
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Services\\USBSTOR"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			//RegSetValueEx(hKey,_T("Start"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD));
			if(RegSetValueEx(hKey,_T("Start"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag=_T("�ѿ���USB�洢�豸���̷��Զ�����\r\n");
			else flag=_T("");
		}		
		RegCloseKey(hKey);
		
	}

	//////////////////////////////////�رյ�USB�Զ�����////////////////////////////////////////
	if(m_Btn2.GetCheck()==1)
	{
		szValue=0xff;
		if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("NoDriveTypeAutoRun"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			{
				//MessageBox(_T("ff"));
				flag+=_T("�ѹر�USB�Զ�����\r\n");
			}
			else flag+=_T("");
		}
		RegCloseKey(hKey);
	}
	if(m_Btn2.GetCheck()==0)
	{
		szValue=0xdd;
		if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("NoDriveTypeAutoRun"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			{
				//MessageBox(_T("dd"));
				flag+=_T("�ѿ���USB�Զ�����\r\n");
			}
			else flag+=_T("");
		}
		RegCloseKey(hKey);
	}


	//////////////////////////////////��ֹ������������Ͽ�����USB�洢�豸//////////////////////////////////////
	if (m_Btn3.GetCheck()==1)
	{
		szValue=1;
		DWORD dwDisposition;
		//DWORD dwordlength = (DWORD)strlen((const char *)ch)+1;
		//RegOpenKey(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Contro"),&hKey);
		LONG lRet=RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
		if (lRet==ERROR_SUCCESS)
		{
			//MessageBox(_T("�ɹ�"));
			RegCloseKey(hKey);
		}
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("WriteProtect"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag+=_T("��ֹ������������Ͽ�����USB�洢�豸");
			else flag+=_T("");
		}
		RegCloseKey(hKey);
	}
	if (m_Btn3.GetCheck()==0)
	{
		szValue=0;
		DWORD dwDisposition;
		LONG lRet=RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
		if (lRet==ERROR_SUCCESS)
		{
			//MessageBox(_T("�ɹ�"));
			RegCloseKey(hKey);
		}
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("WriteProtect"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag+=_T("��������������Ͽ�����USB�洢�豸");
		}
		RegCloseKey(hKey);
	}
	//////////////////////////////////��ʾ��Ϣ////////////////////////////////////////
	MessageBox(flag);
}

HBRUSH CMyDlg4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC&&(pWnd->GetDlgCtrlID()==IDC_STATIC_PS||pWnd->GetDlgCtrlID()==IDC_STATIC_NO))   
	{ 
		pDC-> SetTextColor(RGB(255,0,0));   //�ı��������ɫ 
		pDC-> SetBkMode(TRANSPARENT);   //���ñ���͸��
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH)); 
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CMyDlg4::OnStnClickedStaticPs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HKEY hKey;
	DWORD szValue=0;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableRegistryTools"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("�޸��ɹ�!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg4::OnStnClickedStaticNo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HKEY hKey;
	DWORD szValue=1;
	DWORD dwDisposition;
	LONG lRet=RegCreateKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
	if (lRet==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,_T("DisableRegistryTools"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			MessageBox(_T("�ѽ�ֹ!"));
	}		
	RegCloseKey(hKey);
}
