#pragma once

#include "../Debug/PETool.h"

// CMyDialogResource 对话框

class CMyDialogResource : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogResource)

public:
	CMyDialogResource(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogResource();
	VOID GetInfo();
	PPEstruct pPEstruct;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_TreeCtrl;
	ResourceInfo resourceInfo;
	afx_msg void OnTvnSelchangedTreeRe(NMHDR* pNMHDR, LRESULT* pResult);
};
