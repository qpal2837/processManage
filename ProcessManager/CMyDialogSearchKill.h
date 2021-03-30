#pragma once
#include <string>
#include <vector>
using namespace std;

// CMyDialogSearchKill 对话框

class CMyDialogSearchKill : public CDialogEx {
	DECLARE_DYNAMIC(CMyDialogSearchKill)

public:
	CMyDialogSearchKill(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogSearchKill();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCHKILL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_FilePath;
	VOID SetChoiceFileEdit();
	CEdit m_EditFilePath;
	afx_msg void OnBnClickedButtonSkChoicefile();
	CButton m_ButtonLocal;
	CButton m_ButtonBlack;
	CButton m_ButtonRm;
	CListCtrl m_ListSanf;
	vector<DWORD>blackProcessPID;

	afx_msg void OnBnClickedButtonLocalsk();
	virtual BOOL OnInitDialog();
	int MD5Encrypt(const void* data, size_t len, unsigned char* md5);


	afx_msg void OnBnClickedButtonBlacksk();
	afx_msg void OnBnClickedButtonSkClosep();
	CButton m_ButtonCloseP;
	afx_msg void OnBnClickedButtonSkKilllocal();
	CButton m_ButtonDeLocal;
	CMFCEditBrowseCtrl m_EditBrowseCtrl;
	CButton m_ButtonUp;
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButtonSkUp();
	afx_msg void OnBnClickedButtonRmsk();
	vector<CString>m_pszDriverArray;
	vector<CString>m_pathArray;
	DWORD m_threadFlag;
	vector<HANDLE>fileThreadArray;
	HANDLE checkThread;

	afx_msg void OnBnClickedButtonRmsk2();
	afx_msg void OnBnClickedButtonRmsk3();
	CButton m_ButtonContinue;
	CButton m_ButtonPause;
};
