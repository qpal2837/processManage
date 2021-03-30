// CMyDialogChoiceFile.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogChoiceFile.h"
#include "afxdialogex.h"


// CMyDialogChoiceFile 对话框

IMPLEMENT_DYNAMIC(CMyDialogChoiceFile, CDialogEx)

CMyDialogChoiceFile::CMyDialogChoiceFile(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHOICE_FILE, pParent) {

}

CMyDialogChoiceFile::~CMyDialogChoiceFile() {
}

void CMyDialogChoiceFile::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE, m_ShellTreeCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogChoiceFile, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyDialogChoiceFile::OnBnClickedOk)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MFCSHELLTREE, &CMyDialogChoiceFile::OnTvnSelchangedMfcshelltree)



END_MESSAGE_MAP()


// CMyDialogChoiceFile 消息处理程序


void CMyDialogChoiceFile::OnBnClickedOk() {
	// TODO: 在此添加控件通知处理程序代码
	switch (m_SourseFlag) 	{
	case 1:
		m_CmyDialogGetFileInfo->m_FilePath = m_FilePath;
		m_CmyDialogGetFileInfo->SetChoiceFileEdit();
		break;
	case 2:
		m_CmyDialogSearchKill->m_FilePath = m_FilePath;
		m_CmyDialogSearchKill->SetChoiceFileEdit();
		break;
	}

	CDialogEx::OnOK();
}


void CMyDialogChoiceFile::OnTvnSelchangedMfcshelltree(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_ShellTreeCtrl.GetItemPath(m_FilePath, pNMTreeView->itemNew.hItem);
	*pResult = 0;
}


BOOL CMyDialogChoiceFile::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


