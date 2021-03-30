// CMyDialogGetWindowInfo.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogGetWindowInfo.h"
#include "afxdialogex.h"


// CMyDialogGetWindowInfo 对话框

IMPLEMENT_DYNAMIC(CMyDialogGetWindowInfo, CDialogEx)

CMyDialogGetWindowInfo::CMyDialogGetWindowInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WINDOWINFO, pParent) {

}

CMyDialogGetWindowInfo::~CMyDialogGetWindowInfo() {
}

void CMyDialogGetWindowInfo::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WINDOW_INFO, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogGetWindowInfo, CDialogEx)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_WINDOW_INFO, &CMyDialogGetWindowInfo::OnLvnItemchangedListWindowInfo)
END_MESSAGE_MAP()

BOOL CALLBACK EnumWindowsProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam
) {
	CMyDialogGetWindowInfo* dialog = (CMyDialogGetWindowInfo*)lParam;
	TCHAR buf[20];
	::GetWindowText(hwnd, buf, 20);
	if (IsWindowVisible(hwnd) == true && wcslen(buf) != 0) {
		dialog->m_ListCtrl.InsertItem(dialog->m_Index, buf, 0);
		CString handleValue;
		CString processIdValue;
		DWORD processId;
		::GetWindowThreadProcessId(hwnd, &processId);
		handleValue.Format(_T("0x%d"), hwnd);
		processIdValue.Format(_T("%d"), processId);
		dialog->m_ListCtrl.SetItemText(dialog->m_Index, 1, handleValue);
		dialog->m_ListCtrl.SetItemText(dialog->m_Index, 2, processIdValue);

		dialog->m_Index++;
	}
	return true;
}

DWORD WINAPI GetWindowInfoProc(LPVOID lpThreadParameter) {
	while (true) {
		CMyDialogGetWindowInfo* dialog = (CMyDialogGetWindowInfo*)lpThreadParameter;
		dialog->m_ListCtrl.DeleteAllItems();
		dialog->m_Index = 0;

		EnumWindows(EnumWindowsProc, (LPARAM)dialog);
		Sleep(2500);
	}
	return TRUE;
}
BOOL CMyDialogGetWindowInfo::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"窗口标题", LVCFMT_CENTER, 300);
	m_ListCtrl.InsertColumn(2, L"窗口句柄", LVCFMT_CENTER, 230);
	m_ListCtrl.InsertColumn(2, L"窗口进程PID", LVCFMT_CENTER, 230);

	CreateThread(NULL, NULL, GetWindowInfoProc, (LPVOID)this, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

// CMyDialogGetWindowInfo 消息处理程序
void CMyDialogGetWindowInfo::OnLvnItemchangedListWindowInfo(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
