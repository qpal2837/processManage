#pragma once

#include "../Debug/PETool.h"
// CMyDialogLocation 对话框

class CMyDialogLocation : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogLocation)

public:
	CMyDialogLocation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogLocation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COUNT_LOCATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ButtonVA;
	CButton m_ButtonRVA;
	CButton m_ButtonFOA;
	CEdit m_EditVA;
	CEdit m_EditRVA;
	CEdit m_EditFOA;
	CEdit m_EditSection;
	CEdit m_EditByte;
	PPEstruct pPEstruct;
	afx_msg void OnBnClickedButtonVa();
	afx_msg void OnBnClickedButtonFoa();
	afx_msg void OnBnClickedButtonLocationEnter();
	afx_msg void OnBnClickedButtonRva();
};
