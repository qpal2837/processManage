#pragma once


// CMyDialogService 对话框

class CMyDialogService : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogService)

public:
	CMyDialogService(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogService();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlService;
	afx_msg void OnLvnItemchangedListService(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRClickListService(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_RlickServiceName;
	afx_msg void OnStartService();
	afx_msg void OnCloseService();
};
