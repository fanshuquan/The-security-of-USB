#pragma once


// CCHOOSE �Ի���

class CCHOOSE : public CDialog
{
	DECLARE_DYNAMIC(CCHOOSE)

public:
	CCHOOSE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCHOOSE();

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
};
