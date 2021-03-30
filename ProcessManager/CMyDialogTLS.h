#pragma once

#include "../Debug/PETool.h"
// CMyDialogTLS 对话框

class CMyDialogTLS : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogTLS)

public:
	CMyDialogTLS(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogTLS();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TLS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	PPEstruct pPEstruct;
	virtual BOOL OnInitDialog();
	VOID GetInfo();
};
