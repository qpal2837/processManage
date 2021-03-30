#pragma once

#include <vector>
using namespace std;
// CMyDialogSystemClear 对话框
class CMyDialogSystemClear : public CDialogEx {
	DECLARE_DYNAMIC(CMyDialogSystemClear)

public:
	CMyDialogSystemClear(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogSystemClear();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLEAR_SYSTEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CEdit m_Edit;
	CButton m_Button;
	afx_msg void OnBnClickedButtonClearSystem();
	afx_msg void OnBnClickedButtonScan();
	virtual BOOL OnInitDialog();
	vector<CString>m_deletePath;
	vector<CString>m_Path;
	CButton m_ButtonScanf;
};
