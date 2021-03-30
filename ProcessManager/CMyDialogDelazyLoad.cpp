// CMyDialogDelazyLoad.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogDelazyLoad.h"
#include "afxdialogex.h"


// CMyDialogDelazyLoad 对话框

IMPLEMENT_DYNAMIC(CMyDialogDelazyLoad, CDialogEx)

CMyDialogDelazyLoad::CMyDialogDelazyLoad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELAZYLOAD, pParent)
{

}

CMyDialogDelazyLoad::~CMyDialogDelazyLoad()
{
}

void CMyDialogDelazyLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CMyDialogDelazyLoad, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogDelazyLoad 消息处理程序


BOOL CMyDialogDelazyLoad::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
VOID CMyDialogDelazyLoad::GetInfo() {
	DelayLoadInfo dl;
	GetDelayLoadInfo(&dl,this->pPEstruct);
	CString value(dl.dllName);
	SetDlgItemText(IDC_EDIT_DL_DLLNAME, value);
	value.Format(_T("%08X"),dl.dllNameRva);
	SetDlgItemText(IDC_EDIT_DL_DLLNAMERVA, value);
	value.Format(_T("%08X"), dl.mouduleHandleRva);
	SetDlgItemText(IDC_EDIT_DL_MD_RVA, value);
	value.Format(_T("%08X"), dl.importAddressTableRva);
	SetDlgItemText(IDC_EDIT_DL_IAT_RVA, value);
	value.Format(_T("%08X"), dl.importNameTableRva);
	SetDlgItemText(IDC_EDIT_DL_INT_RVA, value);
	value.Format(_T("%08X"), dl.boundImportAddressTableRva);
	SetDlgItemText(IDC_EDIT_DL_BOUND_RVA, value);
	value.Format(_T("%08X"), dl.unloadInformationTableRva);
	SetDlgItemText(IDC_EDIT_DL_UPRVA, value);
	value.Format(_T("%08X"), dl.timeDateStamp);
	SetDlgItemText(IDC_EDIT_DL_DLLNAMERVA, value);

	return VOID();
}
