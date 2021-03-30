#pragma once


// CMyDiglogProcessMoudle 对话框

class CMyDiglogProcessMoudle : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDiglogProcessMoudle)

public:
	CMyDiglogProcessMoudle(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDiglogProcessMoudle();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESS_MOUDLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ProcessId;
	virtual BOOL OnInitDialog();
	VOID GetMoudlbe();
	CListCtrl m_ListCtrl;
};
