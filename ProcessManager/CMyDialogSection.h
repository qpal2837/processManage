#pragma once

#include "../Debug/PETool.h"


// CMyDialogSection 对话框

class CMyDialogSection : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogSection)

public:
	CMyDialogSection(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogSection();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListSection;
	virtual BOOL OnInitDialog();
	VOID GetInfo();
	PPEstruct pPEstruct;
};
