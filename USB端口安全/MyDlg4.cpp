// MyDlg4.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg4.h"


// CMyDlg4 对话框

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


// CMyDlg4 消息处理程序

BOOL CMyDlg4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	static CFont font;   //定义静态变量
	font.CreatePointFont(140, "隶书");
	GetDlgItem(IDC_STATIC_FONT)->SetFont(&font);

	CBrush m_brush;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMyDlg4::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	/////////////////////////////////关闭USB存储设备的盘符自动分配/////////////////////////////////////////
	HKEY hKey;
	DWORD szValue;
	CString flag;
	if (m_Btn1.GetCheck()==1)
	{
		szValue=4;
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Services\\USBSTOR"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("Start"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag=_T("已关闭USB存储设备的盘符自动分配\r\n");
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
				flag=_T("已开启USB存储设备的盘符自动分配\r\n");
			else flag=_T("");
		}		
		RegCloseKey(hKey);
		
	}

	//////////////////////////////////关闭掉USB自动运行////////////////////////////////////////
	if(m_Btn2.GetCheck()==1)
	{
		szValue=0xff;
		if(RegOpenKeyEx(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("NoDriveTypeAutoRun"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
			{
				//MessageBox(_T("ff"));
				flag+=_T("已关闭USB自动运行\r\n");
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
				flag+=_T("已开启USB自动运行\r\n");
			}
			else flag+=_T("");
		}
		RegCloseKey(hKey);
	}


	//////////////////////////////////禁止将电脑里的资料拷贝到USB存储设备//////////////////////////////////////
	if (m_Btn3.GetCheck()==1)
	{
		szValue=1;
		DWORD dwDisposition;
		//DWORD dwordlength = (DWORD)strlen((const char *)ch)+1;
		//RegOpenKey(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Contro"),&hKey);
		LONG lRet=RegCreateKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,NULL,REG_OPTION_VOLATILE,KEY_WRITE|KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition);
		if (lRet==ERROR_SUCCESS)
		{
			//MessageBox(_T("成功"));
			RegCloseKey(hKey);
		}
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("WriteProtect"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag+=_T("禁止将电脑里的资料拷贝到USB存储设备");
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
			//MessageBox(_T("成功"));
			RegCloseKey(hKey);
		}
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SYSTEM\\CurrentControlSet\\Control\\StorageDevicePolicies"),0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hKey,_T("WriteProtect"),0,REG_DWORD,(const BYTE *)&szValue,sizeof(DWORD))==ERROR_SUCCESS)
				flag+=_T("允许将电脑里的资料拷贝到USB存储设备");
		}
		RegCloseKey(hKey);
	}
	//////////////////////////////////提示信息////////////////////////////////////////
	MessageBox(flag);
}

HBRUSH CMyDlg4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if(nCtlColor == CTLCOLOR_STATIC&&(pWnd->GetDlgCtrlID()==IDC_STATIC_PS||pWnd->GetDlgCtrlID()==IDC_STATIC_NO))   
	{ 
		pDC-> SetTextColor(RGB(255,0,0));   //改变字体的颜色 
		pDC-> SetBkMode(TRANSPARENT);   //设置背景透明
		return   HBRUSH(GetStockObject(HOLLOW_BRUSH)); 
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CMyDlg4::OnStnClickedStaticPs()
{
	// TODO: 在此添加控件通知处理程序代码
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
			MessageBox(_T("修复成功!"));
	}		
	RegCloseKey(hKey);
}

void CMyDlg4::OnStnClickedStaticNo()
{
	// TODO: 在此添加控件通知处理程序代码
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
			MessageBox(_T("已禁止!"));
	}		
	RegCloseKey(hKey);
}
