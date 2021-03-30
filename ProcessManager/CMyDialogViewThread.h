#pragma once


// CMyDialogViewThread 对话框

class CMyDialogViewThread : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogViewThread)

public:
	CMyDialogViewThread(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogViewThread();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIEW_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_ProcessId;
	DWORD m_RClickThreadId;
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	VOID GetThread();
	afx_msg void OnNMRClickListViewThread(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickSuspendThread();
	afx_msg void OnClickResumeThread();
	afx_msg void OnClickFinishThread();
};
