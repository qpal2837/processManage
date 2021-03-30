#pragma once

#include "../Debug/PETool.h"
// CMyDialogDelazyLoad 对话框

class CMyDialogDelazyLoad : public CDialogEx {
	DECLARE_DYNAMIC(CMyDialogDelazyLoad)

public:
	CMyDialogDelazyLoad(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogDelazyLoad();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIALOG_DELAZYLOAD
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	PPEstruct pPEstruct;
	VOID GetInfo();

	virtual BOOL OnInitDialog();
};
