#pragma once

#include "../Debug/PETool.h"
// CMyDialogExportTable 对话框

class CMyDialogExportTable : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogExportTable)

public:
	CMyDialogExportTable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogExportTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT };
#endif
public:
	PPEstruct pPEstruct;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	VOID GetInfo();
	CListCtrl m_ListCtrl;
};
