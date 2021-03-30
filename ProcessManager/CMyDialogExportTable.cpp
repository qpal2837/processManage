// CMyDialogExportTable.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogExportTable.h"
#include "afxdialogex.h"


// CMyDialogExportTable 对话框

IMPLEMENT_DYNAMIC(CMyDialogExportTable, CDialogEx)

CMyDialogExportTable::CMyDialogExportTable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent) {

}

CMyDialogExportTable::~CMyDialogExportTable() {
}

void CMyDialogExportTable::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FUN, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogExportTable, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogExportTable 消息处理程序


BOOL CMyDialogExportTable::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"序号", LVCFMT_CENTER, 100);
	m_ListCtrl.InsertColumn(2, L"RVA", LVCFMT_CENTER, 100);
	m_ListCtrl.InsertColumn(3, L"Offset", LVCFMT_CENTER, 100);
	m_ListCtrl.InsertColumn(4, L"Function Name", LVCFMT_CENTER, 200);

	// TODO:  在此添加额外的初始化
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogExportTable::GetInfo() {
	PExportInfo pExpportInfo;
	GetExportTableInfo(&pExpportInfo, this->pPEstruct);
	CString value;
	value.Format(_T("%08X"), pExpportInfo->exportTableFoaValue);
	SetDlgItemText(IDC_EDIT_EXPORT_RVA, value);
	value.Format(_T("%08X"), pExpportInfo->feature);
	SetDlgItemText(IDC_EDIT_EXPORT_FEATURE, value);
	value.Format(_T("%08X"), pExpportInfo->base);
	SetDlgItemText(IDC_EDIT_EXPORT_IMAGEBASE, value);
	value.Format(_T("%08X"), pExpportInfo->nameRva);
	SetDlgItemText(IDC_EDIT_EXPORT_NAME_RVA, value);
	value=(pExpportInfo->name);
	SetDlgItemText(IDC_EDIT_EXPORT_NAME, value);
	value.Format(_T("%08X"), pExpportInfo->funCount);
	SetDlgItemText(IDC_EDIT_EXPORT_FUNCOUNT, value);
	value.Format(_T("%08X"), pExpportInfo->funNameCount);
	SetDlgItemText(IDC_EDIT_EXPORT_FUNNAMECOUNT, value);
	value.Format(_T("%08X"), pExpportInfo->funAddressRva);
	SetDlgItemText(IDC_EDIT_EXPORT_FUN_ADDRESS, value);
	value.Format(_T("%08X"), pExpportInfo->funNameAddressRva);
	SetDlgItemText(IDC_EDIT_EXPORT_FUNNAME_ADDRESS, value);
	value.Format(_T("%08X"), pExpportInfo->funNumberAddressRva);
	SetDlgItemText(IDC_EDIT_EXPORT_FUNNUMBER_ADDRESS, value);
	for (int i = 0; i < pExpportInfo->funCount; i++) {
		CString value;
		value.Format(_T("%d"), pExpportInfo->pFuntionInfo[i].ordinal);
		m_ListCtrl.InsertItem(i, value, 0);
		value.Format(_T("%08X"), pExpportInfo->pFuntionInfo[i].rva);
		m_ListCtrl.SetItemText(i, 1, value);
		value.Format(_T("%08X"), pExpportInfo->pFuntionInfo[i].offset);
		m_ListCtrl.SetItemText(i, 2, value);
		value = (pExpportInfo->pFuntionInfo[i].funtionName);
		m_ListCtrl.SetItemText(i, 3, value);
	}
	return VOID();
}
