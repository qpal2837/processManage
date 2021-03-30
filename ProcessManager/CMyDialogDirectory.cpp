// CMyDialogDirectory.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogDirectory.h"
#include "afxdialogex.h"
#include "CMyDialogExportTable.h"
#include "CMyDialogImportTable.h"
#include "CMyDialogRelacationTable.h"
#include "CMyDialogDelazyLoad.h"
#include "CMyDialogTLS.h"
#include "CMyDialogResource.h"

#pragma comment(lib,"../Debug/PETool.lib") 

// CMyDialogDirectory 对话框

IMPLEMENT_DYNAMIC(CMyDialogDirectory, CDialogEx)

CMyDialogDirectory::CMyDialogDirectory(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DIRECTORY, pParent) {

}

CMyDialogDirectory::~CMyDialogDirectory() {
}


void CMyDialogDirectory::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialogDirectory, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_INFO, &CMyDialogDirectory::OnBnClickedButtonExportInfo)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_INFO, &CMyDialogDirectory::OnBnClickedButtonImportInfo)
	ON_BN_CLICKED(IDC_BUTTON_RELACATION_INFO, &CMyDialogDirectory::OnBnClickedButtonRelacationInfo)

	ON_BN_CLICKED(IDC_BUTTON_LAZYLOAD, &CMyDialogDirectory::OnBnClickedButtonLazyload)
	ON_BN_CLICKED(IDC_BUTTON_TLS_INFO, &CMyDialogDirectory::OnBnClickedButtonTlsInfo)
	ON_EN_CHANGE(IDC_EDIT_EXPORT_SIZE, &CMyDialogDirectory::OnEnChangeEditExportSize)
	ON_BN_CLICKED(IDC_BUTTON_RESOURCE_INFO, &CMyDialogDirectory::OnBnClickedButtonResourceInfo)
END_MESSAGE_MAP()


// CMyDialogDirectory 消息处理程序


BOOL CMyDialogDirectory::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
VOID CMyDialogDirectory::GetInfo() {
	PDirectoryInfo pDirectoryInfo = NULL;
	GetDirectoryInfo(&pDirectoryInfo, this->pPEstruct);
	CString value;
	value.Format(_T("%08X"), pDirectoryInfo[0].virtualAdress);
	SetDlgItemText(IDC_EDIT_EXPORT_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[0].size);
	SetDlgItemText(IDC_EDIT_EXPORT_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[1].virtualAdress);
	SetDlgItemText(IDC_EDIT_IMPORT_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[1].size);
	SetDlgItemText(IDC_EDIT_IMPORT_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[2].virtualAdress);
	SetDlgItemText(IDC_EDIT_RESOURCE_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[2].size);
	SetDlgItemText(IDC_EDIT_RESOURCE_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[3].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[3].size);
	SetDlgItemText(IDC_EDIT_LY_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[4].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA2, value);
	value.Format(_T("%08X"), pDirectoryInfo[4].size);
	SetDlgItemText(IDC_EDIT_LY_SIZE2, value);

	value.Format(_T("%08X"), pDirectoryInfo[5].virtualAdress);
	SetDlgItemText(IDC_EDIT_RELACATION_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[5].size);
	SetDlgItemText(IDC_EDIT_RELACATION_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[6].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA3, value);
	value.Format(_T("%08X"), pDirectoryInfo[6].size);
	SetDlgItemText(IDC_EDIT_LY_SIZE3, value);

	value.Format(_T("%08X"), pDirectoryInfo[7].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA4, value);
	value.Format(_T("%08X"), pDirectoryInfo[7].size);
	SetDlgItemText(IDC_EDIT_LY_SIZE4, value);

	value.Format(_T("%08X"), pDirectoryInfo[8].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA5, value);
	value.Format(_T("%08X"), pDirectoryInfo[8].size);
	SetDlgItemText(IDC_EDIT_LY_SIZE5, value);

	value.Format(_T("%08X"), pDirectoryInfo[9].virtualAdress);
	SetDlgItemText(IDC_EDIT_TLS_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[9].size);
	SetDlgItemText(IDC_EDIT_TLS_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[10].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA6, value);
	value.Format(_T("%08X"), pDirectoryInfo[10].size);
	SetDlgItemText(IDC_EDIT_LY_RVA7, value);

	value.Format(_T("%08X"), pDirectoryInfo[11].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA6, value);
	value.Format(_T("%08X"), pDirectoryInfo[11].size);
	SetDlgItemText(IDC_EDIT_LY_RVA7, value);

	value.Format(_T("%08X"), pDirectoryInfo[12].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA8, value);
	value.Format(_T("%08X"), pDirectoryInfo[12].size);
	SetDlgItemText(IDC_EDIT_LY_RVA9, value);


	value.Format(_T("%08X"), pDirectoryInfo[13].virtualAdress);
	SetDlgItemText(IDC_EDIT_LAZYLOAD_RVA, value);
	value.Format(_T("%08X"), pDirectoryInfo[13].size);
	SetDlgItemText(IDC_EDIT_LAZYLOAD_SIZE, value);

	value.Format(_T("%08X"), pDirectoryInfo[14].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA10, value);
	value.Format(_T("%08X"), pDirectoryInfo[14].size);
	SetDlgItemText(IDC_EDIT_LY_RVA11, value);

	value.Format(_T("%08X"), pDirectoryInfo[15].virtualAdress);
	SetDlgItemText(IDC_EDIT_LY_RVA12, value);
	value.Format(_T("%08X"), pDirectoryInfo[15].size);
	SetDlgItemText(IDC_EDIT_LY_RVA13, value);




	return VOID();
}


void CMyDialogDirectory::OnBnClickedButtonExportInfo() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogExportTable cMydialogExportTalbe;
	cMydialogExportTalbe.pPEstruct = this->pPEstruct;
	cMydialogExportTalbe.DoModal();
}


void CMyDialogDirectory::OnBnClickedButtonImportInfo() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogImportTable cMyDialogImportTable;
	cMyDialogImportTable.pPEstruct = this->pPEstruct;
	cMyDialogImportTable.DoModal();
}


void CMyDialogDirectory::OnBnClickedButtonRelacationInfo() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogRelacationTable cMydialogRelacationTable;
	cMydialogRelacationTable.pPEstruct = this->pPEstruct;
	cMydialogRelacationTable.DoModal();
}



void CMyDialogDirectory::OnBnClickedButtonLazyload() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogDelazyLoad cMyDialogDelazyLoad;
	cMyDialogDelazyLoad.pPEstruct = this->pPEstruct;
	cMyDialogDelazyLoad.DoModal();
	
}


void CMyDialogDirectory::OnBnClickedButtonTlsInfo() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogTLS cMyDialogTLS;
	cMyDialogTLS.pPEstruct = this->pPEstruct;
	cMyDialogTLS.DoModal();
}


void CMyDialogDirectory::OnEnChangeEditExportSize() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMyDialogDirectory::OnBnClickedButtonResourceInfo() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogResource dialog;
	dialog.pPEstruct = this->pPEstruct;
	dialog.DoModal();
}
