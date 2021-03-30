#pragma once


// CMyDialogViewHeap 对话框

class CMyDialogViewHeap : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogViewHeap)

public:
	CMyDialogViewHeap(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogViewHeap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIEW_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_ProcessId;
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	VOID GetHeap();
};
