#pragma once


// CCHOOSE 对话框

class CCHOOSE : public CDialog
{
	DECLARE_DYNAMIC(CCHOOSE)

public:
	CCHOOSE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCHOOSE();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
};
