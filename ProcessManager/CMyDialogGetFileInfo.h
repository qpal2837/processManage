#pragma once

#include "CMyDialogGetFileInfo.h"
#include <vector>
using namespace std;
// CMyDialogGetFileInfo 对话框

class CMyDialogGetFileInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogGetFileInfo)

public:
	CMyDialogGetFileInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyDialogGetFileInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenChoiceFile();
	VOID SetChoiceFileEdit();
	VOID GetFileInfoByPath();
	CString m_FilePath;
	CEdit m_EditFilePath;
	CEdit m_EditFileInfo;
	vector<CString>m_ClearSuffix;
	vector<CString>m_DeleteFilePath;
	virtual BOOL OnInitDialog();
	VOID MyGetFileSize(CString path, DWORD& fileSize, DWORD& deleteFileSize);
	CEdit m_EditDelete;
	CButton m_ButtonDelete;
	afx_msg void OnBnClickedButtonDelete();
};
