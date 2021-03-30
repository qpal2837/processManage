// CMyDialogSystemClear.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogSystemClear.h"
#include "afxdialogex.h"



// CMyDialogSystemClear 对话框

IMPLEMENT_DYNAMIC(CMyDialogSystemClear, CDialogEx)

CMyDialogSystemClear::CMyDialogSystemClear(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLEAR_SYSTEM, pParent) {

}

CMyDialogSystemClear::~CMyDialogSystemClear() {
}

void CMyDialogSystemClear::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLEAR_SYSTEM, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_CLEAR_SYSTEM_TIP, m_Edit);
	DDX_Control(pDX, IDC_BUTTON_CLEAR_SYSTEM, m_Button);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_ButtonScanf);
}


BEGIN_MESSAGE_MAP(CMyDialogSystemClear, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_SYSTEM, &CMyDialogSystemClear::OnBnClickedButtonClearSystem)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CMyDialogSystemClear::OnBnClickedButtonScan)
END_MESSAGE_MAP()


// CMyDialogSystemClear 消息处理程序


DWORD WINAPI DeleteFileProc(LPVOID lpThreadParameter) {
	CMyDialogSystemClear* dialog = (CMyDialogSystemClear*)lpThreadParameter;
	
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < dialog->m_deletePath.size(); i++) {
		//DeleteFile(m_deletePath[i]);
		CString value;
		value.Format(_T("已删除%d个文件"), i + 1);
		dialog->m_Edit.SetWindowTextW(value);
	}
	dialog->m_ListCtrl.DeleteAllItems();
	dialog->MessageBox(_T("删除成功!"));
	dialog->m_ButtonScanf.EnableWindow(TRUE);

	return true;
}
void CMyDialogSystemClear::OnBnClickedButtonClearSystem() {
	m_ButtonScanf.EnableWindow(FALSE);
	m_Button.EnableWindow(FALSE);
	CreateThread(NULL, NULL, DeleteFileProc, (LPVOID)this, NULL, NULL);
}

VOID ScanfSystemFile(CString path, DWORD& sumDeleteFileSize, DWORD& count, CMyDialogSystemClear* dialog) {
	CString tempPath = _T("");
	CString perfectTempPath = _T("");
	tempPath = path;
	tempPath += "\\*";
	WIN32_FIND_DATA wfd = {};
	HANDLE hFile = FindFirstFile(tempPath, &wfd);
	do {
		if (StrCmp(wfd.cFileName, L".") == 0 || StrCmp(wfd.cFileName, L"..") == 0) {
			continue;
		}
		perfectTempPath = path;
		perfectTempPath += "\\";
		perfectTempPath += wfd.cFileName;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			ScanfSystemFile(perfectTempPath, sumDeleteFileSize, count, dialog);
		}
		else {
			int value = perfectTempPath.ReverseFind('.');
			if (value != -1) {
				CString sub = perfectTempPath;
				sub.Delete(0, value);
				dialog->m_ListCtrl.InsertItem(count, perfectTempPath, 0);
				dialog->m_deletePath.push_back(perfectTempPath);
				DWORD size = (wfd.nFileSizeHigh * (0 + 1) + wfd.nFileSizeLow);
				sumDeleteFileSize += size;
				CString value;
				value.Format(_T("%dKB"), size / 1024 == 0 ? 1 : size / 1024);
				dialog->m_ListCtrl.SetItemText(count, 1, value);
				count++;
				value.Format(_T("扫描出可删除文件:%d个,共计大小:%d MB"), count, sumDeleteFileSize / 1024 / 1024);
				dialog->m_Edit.SetWindowTextW(value);
			}
		}
	} while (FindNextFile(hFile, &wfd));
}

DWORD WINAPI ScanfSystemFileProc(LPVOID lpThreadParameter) {
	CMyDialogSystemClear* dialog = (CMyDialogSystemClear*)lpThreadParameter;
	dialog->m_Button.EnableWindow(FALSE);
	DWORD count = 0;
	DWORD sumDeleteSize = 0;
	dialog->m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < dialog->m_Path.size(); i++) {
		ScanfSystemFile(dialog->m_Path[i], sumDeleteSize, count, dialog);
	}
	dialog->m_Button.EnableWindow(TRUE);
	dialog->MessageBox(_T("扫描完成!"));
	return true;
}

void CMyDialogSystemClear::OnBnClickedButtonScan() {
	// TODO: 在此添加控件通知处理程序代码
	CreateThread(NULL, NULL, ScanfSystemFileProc, (LPVOID)this, NULL, NULL);
}


BOOL CMyDialogSystemClear::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"文件位置", LVCFMT_CENTER, 500);
	m_ListCtrl.InsertColumn(2, L"大小", LVCFMT_CENTER, 120);
	CString m_WindowsTemp;
	CString m_AppdataTemp;
	m_WindowsTemp = _T("C:\\Windows\\Temp");

	DWORD dwSize;
	TCHAR name[0x20] = { 0 };
	GetUserName(name, &dwSize);
	m_AppdataTemp.Format(_T("C:\\Users\\%s\\AppData\\Local\\Temp"), name);
	m_Path.push_back(m_WindowsTemp);
	m_Path.push_back(m_AppdataTemp);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
