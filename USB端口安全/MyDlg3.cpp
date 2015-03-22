// MyDlg3.cpp : 实现文件
//

#include "stdafx.h"
#include "USB端口安全.h"
#include "MyDlg3.h"


// CMyDlg3 对话框

IMPLEMENT_DYNAMIC(CMyDlg3, CDialog)

CMyDlg3::CMyDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg3::IDD, pParent)
{

}

CMyDlg3::~CMyDlg3()
{
}

void CMyDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_historylist);
}


BEGIN_MESSAGE_MAP(CMyDlg3, CDialog)
END_MESSAGE_MAP()


// CMyDlg3 消息处理程序



// void CMyDlg3::QueryKeyV(HKEY hKey,TCHAR stri[]) 
// { 
// 	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
// 	DWORD    cbName;                   // size of name string 
// 	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
// 	DWORD    cchClassName = MAX_PATH;  // size of class string 
// 	DWORD    cSubKeys=0;               // number of subkeys 
// 	DWORD    cbMaxSubKey;              // longest subkey size 
// 	DWORD    cchMaxClass;              // longest class string 
// 	DWORD    cValues;              // number of values for key 
// 	DWORD    cchMaxValue;          // longest value name 
// 	DWORD    cbMaxValueData;       // longest value data 
// 	DWORD    cbSecurityDescriptor; // size of security descriptor 
// 	FILETIME ftLastWriteTime;      // last write time 
// 
// 	DWORD i, retCode; 
// 
// 	TCHAR  achValue[MAX_VALUE_NAME]; 
// 	DWORD cchValue = MAX_VALUE_NAME; 
// 
// 	// Get the class name and the value count. 
// 	retCode = RegQueryInfoKey(
// 		hKey,                    // key handle 
// 		achClass,                // buffer for class name 
// 		&cchClassName,           // size of class string 
// 		NULL,                    // reserved 
// 		&cSubKeys,               // number of subkeys 
// 		&cbMaxSubKey,            // longest subkey size 
// 		&cchMaxClass,            // longest class string 
// 		&cValues,                // number of values for this key 
// 		&cchMaxValue,            // longest value name 
// 		&cbMaxValueData,         // longest value data 
// 		&cbSecurityDescriptor,   // security descriptor 
// 		&ftLastWriteTime);       // last write time 
// 
// 
// 	// Enumerate the key values. 
// 
// 	if (cValues) 
// 	{
// 		printf( "Number of values: %d\n", cValues);
// 
// 		for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
// 		{ 
// 			cchValue = MAX_VALUE_NAME; 
// 			achValue[0] = '\0'; 
// 			retCode = RegEnumValue(hKey, i, 
// 				achValue, 
// 				&cchValue, 
// 				NULL, 
// 				NULL,
// 				NULL,
// 				NULL);
// 
// 			if (retCode == ERROR_SUCCESS ) 
// 			{ 
// 				_tprintf(TEXT("(%d) %s\n"), i+1, achValue);
// 			} 
// 		}
// 	}
// }



CString CMyDlg3::finder(HKEY hvKey,int i,CString str)
{
	DWORD dwSize = 0;
	BYTE *pszBuf = NULL;
	CString regVal;
	LONG lRet = RegQueryValueEx(hvKey, str, NULL, NULL, NULL, &dwSize);
	if(lRet == ERROR_SUCCESS && dwSize > 0){
		pszBuf = new BYTE[dwSize+1];
		ZeroMemory(pszBuf, dwSize+1);
		RegQueryValueEx(hvKey,str, NULL, NULL, pszBuf, &dwSize);
	}
	regVal.Format(_T("%s"), pszBuf);
// 	if(_tcscmp(str,_T("")))
// 	m_historylist.InsertItem(i,regVal);
	if (pszBuf) delete [] pszBuf;
	return regVal;
}

void CMyDlg3::QueryKey(HKEY hKey,TCHAR stri[]) 
{ 
	HKEY hvKey;
	TCHAR    str[MAX_KEY_LENGTH];
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys=0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode; 

//	TCHAR  achValue[MAX_VALUE_NAME]; 
	DWORD cchValue = MAX_VALUE_NAME; 

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	// Enumerate the subkeys, until RegEnumKeyEx fails.

	if (cSubKeys)
	{
		//printf( "\nNumber of subkeys: %d\n", cSubKeys);

		for (i=0; i<cSubKeys; i++) 
		{ 
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey, 
				&cbName, 
				NULL, 
				NULL, 
				NULL, 
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS) 
			{
				//_tprintf(TEXT("(%d) %s\n"), i+1, achKey);
				_tcscpy_s(str,stri);
				_tcscat_s(str,TEXT("\\"));
				_tcscat_s(str,achKey);
				//_tprintf(TEXT("%s\n"),str);
				if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
					str/*TEXT("SYSTEM\\ControlSet001\\Enum\\USBSTOR\\")*/,
					0,
					KEY_READ,
					&hvKey) == ERROR_SUCCESS)
				{
					CString regVal,instr;
					instr=_T("FriendlyName");
					regVal=finder(hvKey,i,instr);
					m_historylist.InsertItem(i,regVal);
					instr=_T("Class");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,9,regVal);
					instr=_T("ClassGUID");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,2,regVal);
					instr=_T("CompatibleIDs");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,3,regVal);
					instr=_T("ContainerID");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,4,regVal);
					instr=_T("DeviceDesc");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,5,regVal);
					instr=_T("Driver");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,6,regVal);
					instr=_T("HardwareID");
					regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,7,regVal);
// 					instr=_T("Mfg");
// 					regVal=finder(hvKey,i,instr);
// 					m_historylist.SetItemText(i,8,regVal);
 				    instr=_T("Service");
 				    regVal=finder(hvKey,i,instr);
					m_historylist.SetItemText(i,8,regVal);

					COleDateTime  dt(ftLastWriteTime);
					regVal=dt.Format(_T("%Y-%m-%d  %H:%M:%S"));
					m_historylist.SetItemText(i,1,regVal);
				}
				RegCloseKey(hvKey);
			}
		}
	} 

	
}
BOOL CMyDlg3::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_historylist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_historylist.InsertColumn(0,_T("USB设备名称"),LVCFMT_LEFT,200);
	m_historylist.InsertColumn(1,_T("Last Write Time"),LVCFMT_LEFT,120);	
	m_historylist.InsertColumn(2,_T("ClassGUID"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(3,_T("CompatibleIDs"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(4,_T("ContainerID"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(5,_T("DeviceDesc"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(6,_T("Driver"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(7,_T("HardwareID"),LVCFMT_LEFT,100);
	//m_historylist.InsertColumn(8,_T("Mfg"),LVCFMT_LEFT,100);
	m_historylist.InsertColumn(8,_T("Service"),LVCFMT_LEFT,60);
	m_historylist.InsertColumn(9,_T("Class"),LVCFMT_LEFT,70);
// 	m_historylist.InsertColumn(11,_T("friendlyname"),LVCFMT_LEFT,100);
// 	m_historylist.InsertColumn(12,_T("friendlyname"),LVCFMT_LEFT,100);

	// TODO:  在此添加额外的初始化
	HKEY hKey;
	HKEY h1Key;

	TCHAR    str[MAX_KEY_LENGTH];
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name	
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys=0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

//	TCHAR  achValue[MAX_VALUE_NAME]; 
	DWORD cchValue = MAX_VALUE_NAME; 

	if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
		TEXT("SYSTEM\\ControlSet001\\Enum\\USBSTOR\\"),
		0,
		KEY_READ,
		&hKey) == ERROR_SUCCESS
		)
	{
		//QueryKey(hKey);
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time
		if (cSubKeys)
		{
			//printf( "Number of subkeys: %d\n", cSubKeys);
			for (i=0; i<cSubKeys; i++) 
			{ 
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hKey, i,
					achKey, 
					&cbName, 
					NULL, 
					NULL, 
					NULL, 
					&ftLastWriteTime); 
				if (retCode == ERROR_SUCCESS) 
				{
					//_tprintf(TEXT("(%d) %s"), i+1, achKey);
					_tcscpy_s(str,TEXT("SYSTEM\\ControlSet001\\Enum\\USBSTOR\\"));
					_tcscat_s(str,achKey);
					if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
						str/*TEXT("SYSTEM\\ControlSet001\\Enum\\USBSTOR\\")*/,
						0,
						KEY_READ,
						&h1Key) == ERROR_SUCCESS)
					{
						QueryKey(h1Key,str);										 					
					}
				}
			}
		} 
	}

	RegCloseKey(hKey);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
