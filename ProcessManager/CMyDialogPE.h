#pragma once

#include "CMyDialogSection.h"


// CMyDialogPE 对话框

class CMyDialogPE : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogPE)

public:
	CMyDialogPE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogPE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ButtonSection;
	CButton m_ButtonDirecty;
	CButton m_ButtonLocation;
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	char filePath[MAX_PATH];
	VOID InitPEInfo();
	PPEstruct pPEstruct;
	afx_msg void OnBnClickedButtonSection();
	afx_msg void OnBnClickedButtonDirecrytion();
	afx_msg void OnBnClickedButtonLocation();
};
