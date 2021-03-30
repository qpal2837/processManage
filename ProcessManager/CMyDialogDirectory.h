#pragma once

#include "../Debug/PETool.h"

// CMyDialogDirectory 对话框

class CMyDialogDirectory : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogDirectory)

public:
	CMyDialogDirectory(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogDirectory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIRECTORY };
#endif
public:
	VOID GetInfo();
	PPEstruct pPEstruct;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonExportInfo();
	afx_msg void OnBnClickedButtonImportInfo();
	afx_msg void OnBnClickedButtonRelacationInfo();
	afx_msg void OnBnClickedButtonLazyload();
	afx_msg void OnBnClickedButtonTlsInfo();
	afx_msg void OnEnChangeEditExportSize();
	afx_msg void OnBnClickedButtonResourceInfo();
};
