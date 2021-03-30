#pragma once


// CMyDialogGetWindowInfo 对话框

class CMyDialogGetWindowInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogGetWindowInfo)

public:
	CMyDialogGetWindowInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogGetWindowInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WINDOWINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	DWORD m_Index = 0;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListWindowInfo(NMHDR* pNMHDR, LRESULT* pResult);
};
