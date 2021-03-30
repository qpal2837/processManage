#pragma once

#include "../Debug/PETool.h"

// CMyDialogImportTable 对话框

class CMyDialogImportTable : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogImportTable)

public:
	CMyDialogImportTable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogImportTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlDLl;
	CListCtrl m_ListCtrlFun;
	PPEstruct pPEstruct;
	virtual BOOL OnInitDialog();
	VOID GetInfo();
	VOID GetFun(DWORD index);
	PDll pdll;
	DWORD dllLength;
	afx_msg void OnNMClickListImportDll(NMHDR* pNMHDR, LRESULT* pResult);
};
