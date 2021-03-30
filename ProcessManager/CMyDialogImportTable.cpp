// CMyDialogImportTable.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogImportTable.h"
#include "afxdialogex.h"


// CMyDialogImportTable 对话框

IMPLEMENT_DYNAMIC(CMyDialogImportTable, CDialogEx)

CMyDialogImportTable::CMyDialogImportTable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMPORT, pParent) {

}

CMyDialogImportTable::~CMyDialogImportTable() {
}

void CMyDialogImportTable::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMPORT_DLL, m_ListCtrlDLl);
	DDX_Control(pDX, IDC_LIST_IMPORT_FUN, m_ListCtrlFun);
}


BEGIN_MESSAGE_MAP(CMyDialogImportTable, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMPORT_DLL, &CMyDialogImportTable::OnNMClickListImportDll)
END_MESSAGE_MAP()


// CMyDialogImportTable 消息处理程序


BOOL CMyDialogImportTable::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlDLl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlDLl.InsertColumn(1, L"DllName", LVCFMT_CENTER, 100);
	m_ListCtrlDLl.InsertColumn(2, L"OriginalFirstThunk", LVCFMT_CENTER, 150);
	m_ListCtrlDLl.InsertColumn(3, L"TimeDateStamp", LVCFMT_CENTER, 150);
	m_ListCtrlDLl.InsertColumn(4, L"ForwarderChain", LVCFMT_CENTER, 150);
	m_ListCtrlDLl.InsertColumn(5, L"名称", LVCFMT_CENTER, 150);
	m_ListCtrlDLl.InsertColumn(6, L"FirstThunk", LVCFMT_CENTER, 100);

	m_ListCtrlFun.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlFun.InsertColumn(1, L"ThunkRva", LVCFMT_CENTER, 100);
	m_ListCtrlFun.InsertColumn(2, L"ThunOffset", LVCFMT_CENTER, 100);
	m_ListCtrlFun.InsertColumn(3, L"ThunkValue", LVCFMT_CENTER, 100);
	m_ListCtrlFun.InsertColumn(4, L"Hint", LVCFMT_CENTER, 100);
	m_ListCtrlFun.InsertColumn(5, L"ApiName", LVCFMT_CENTER, 200);

	GetInfo();
	GetFun(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogImportTable::GetInfo() {
	GetImportTableInfo(&pdll, dllLength, this->pPEstruct);
	for (int i = 0; i < dllLength; i++) {
		CString value;
		value = (pdll[i].DllName);
		m_ListCtrlDLl.InsertItem(i, value, 0);
		value.Format(_T("%08X"), pdll[i].OriginalFirstThunk);
		m_ListCtrlDLl.SetItemText(i, 1, value);
		value.Format(_T("%08X"), pdll[i].TimeDateStamp);
		m_ListCtrlDLl.SetItemText(i, 2, value);
		value.Format(_T("%08X"), pdll[i].ForWarderChain);
		m_ListCtrlDLl.SetItemText(i, 3, value);
		value.Format(_T("%08X"), pdll[i].Name);
		m_ListCtrlDLl.SetItemText(i, 4, value);
		value.Format(_T("%08X"), pdll[i].FirstThunk);
		m_ListCtrlDLl.SetItemText(i, 5, value);
	}
	return VOID();
}

VOID CMyDialogImportTable::GetFun(DWORD index) {
	if (index >= dllLength || index < 0) {
	return ;
	}
		m_ListCtrlFun.DeleteAllItems();
	for (int i = 0; i < pdll[index].ApiLength; i++) {
		CString value;
		value.Format(_T("%08X"), pdll[index].pApi[i].ThunkRva);
		m_ListCtrlFun.InsertItem(i, value, 0);
		value.Format(_T("%08X"), pdll[index].pApi[i].ThunkOffset);
		m_ListCtrlFun.SetItemText(i, 1, value);
		value.Format(_T("%08X"), pdll[index].pApi[i].ThunkValue);
		m_ListCtrlFun.SetItemText(i, 2, value);
		value.Format(_T("%04X"), pdll[index].pApi[i].Hnit);
		m_ListCtrlFun.SetItemText(i, 3, value);
		value = (pdll[index].pApi[i].ApiName);
		m_ListCtrlFun.SetItemText(i, 4, value);
	}
	return VOID();
}


void CMyDialogImportTable::OnNMClickListImportDll(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	GetFun(pNMItemActivate->iItem);
	*pResult = 0;
}
