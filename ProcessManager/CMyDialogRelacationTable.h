#pragma once
#include "../Debug/PETool.h"


// CMyDialogRelacationTable 对话框

class CMyDialogRelacationTable : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogRelacationTable)

public:
	CMyDialogRelacationTable(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogRelacationTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELACATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrlSection;
	CListCtrl m_ListCtrlPiece;
	PPEstruct pPEstruct;
	vector<PSectionInfo>sectionInfoArray;
	DWORD sectionLength;
	virtual BOOL OnInitDialog();
	VOID GetInfo();
	VOID GetPiece(DWORD index);
	afx_msg void OnNMClickListRelacationSection(NMHDR* pNMHDR, LRESULT* pResult);
};
