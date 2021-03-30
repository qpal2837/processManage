#pragma once

#include "CMyDialogGetFileInfo.h"
#include "CMyDialogSearchKill.h"
// CMyDialogChoiceFile 对话框

class CMyDialogChoiceFile : public CDialogEx {
	DECLARE_DYNAMIC(CMyDialogChoiceFile)

public:
	CMyDialogChoiceFile(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogChoiceFile();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHOICE_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTvnSelchangedMfcshelltree(NMHDR* pNMHDR, LRESULT* pResult);
	CMFCShellTreeCtrl m_ShellTreeCtrl;
	CString m_FilePath;
	DWORD m_SourseFlag;
	CMyDialogGetFileInfo* m_CmyDialogGetFileInfo;
	CMyDialogSearchKill* m_CmyDialogSearchKill;
	virtual BOOL OnInitDialog();

};
