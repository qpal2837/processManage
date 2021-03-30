#pragma once


// CMyProcessDialog 对话框

class CMyProcessDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyProcessDialog)

public:
	CMyProcessDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyProcessDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MYPROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
	DWORD m_RclickProcessId;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRClickListProcess(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewMoudle();
	afx_msg void OnFinishProcess();

protected:
	afx_msg LRESULT OnUpdateStatusInfo(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickGetThread();
	afx_msg void OnClikViewHeap();
	afx_msg void OnLvnItemchangedListProcess(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProcessPotection();
};
