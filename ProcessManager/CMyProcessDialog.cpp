// CMyProcessDialog.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyProcessDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include <tchar.h>
#include <vector>
#include "CMyDiglogProcessMoudle.h"
#include "CMyDialogViewThread.h"
#include "CMyDialogViewHeap.h"
using namespace std;


const char* processPotectionDllPath = "D:\\MyCode\\c++\\ProcessManager\\Debug\\ProcessPotectionDllPath.dll";
// CMyProcessDialog 对话框

IMPLEMENT_DYNAMIC(CMyProcessDialog, CDialogEx)

CMyProcessDialog::CMyProcessDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MYPROCESS, pParent) {

}

CMyProcessDialog::~CMyProcessDialog() {
}

void CMyProcessDialog::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyProcessDialog, CDialogEx)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROCESS, &CMyProcessDialog::OnNMRClickListProcess)
	ON_COMMAND(ID_32771, &CMyProcessDialog::OnViewMoudle)
	ON_COMMAND(ID_32772, &CMyProcessDialog::OnFinishProcess)
	ON_COMMAND(ID_32773, &CMyProcessDialog::OnClickGetThread)
	ON_COMMAND(ID_32777, &CMyProcessDialog::OnClikViewHeap)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROCESS, &CMyProcessDialog::OnLvnItemchangedListProcess)
	ON_COMMAND(ID_32789, &CMyProcessDialog::OnProcessPotection)
END_MESSAGE_MAP()


// CMyProcessDialog 消息处理程序

DWORD WINAPI GetProressInfo(LPVOID lpThreadParameter) {
	CMyProcessDialog* cMyProcessDialog;
	HANDLE hSnapshot;
	PROCESSENTRY32 pe32;
	int n;
	int nLast;
	TCHAR buf[10];
	BOOL bSucess;
	int i = 0;
	while (true) {
		cMyProcessDialog = (CMyProcessDialog*)lpThreadParameter;
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		pe32 = { sizeof(PROCESSENTRY32) };
		bSucess = Process32First(hSnapshot, &pe32);
		n = cMyProcessDialog->m_ListCtrl.GetTopIndex();
		nLast = n + cMyProcessDialog->m_ListCtrl.GetCountPerPage();
		cMyProcessDialog->m_ListCtrl.DeleteAllItems();
		if (bSucess == true) {
			i = 0;
			do {
				_stprintf_s(buf, _T("%ld"), pe32.th32ProcessID);
				cMyProcessDialog->m_ListCtrl.InsertItem(i, buf, 0);

				cMyProcessDialog->m_ListCtrl.SetItemText(i, 1, pe32.szExeFile);

				_stprintf_s(buf, _T("%d"), pe32.pcPriClassBase);
				cMyProcessDialog->m_ListCtrl.SetItemText(i, 2, buf);

				_stprintf_s(buf, _T("%d"), pe32.cntThreads);
				cMyProcessDialog->m_ListCtrl.SetItemText(i, 3, buf);
				i++;
			} while (Process32Next(hSnapshot, &pe32));
		}
		cMyProcessDialog->m_ListCtrl.EnsureVisible(nLast - 1, TRUE);
		CloseHandle(hSnapshot);
		Sleep(5000);
	}
}

BOOL CMyProcessDialog::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 设置列表风格: 整行选中 + 表格线
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(0, L"PID", LVCFMT_CENTER, 120);
	m_ListCtrl.InsertColumn(1, L"进程名称", LVCFMT_CENTER, 240);
	m_ListCtrl.InsertColumn(2, L"优先级", LVCFMT_CENTER, 160);
	m_ListCtrl.InsertColumn(3, L"线程数量", LVCFMT_CENTER, 160);
	HANDLE GetProressInfoThread = CreateThread(NULL, NULL, GetProressInfo, (LPVOID)this, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CMyProcessDialog::OnTimer(UINT_PTR nIDEvent) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}




void CMyProcessDialog::OnNMRClickListProcess(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1) {
		POINT point = { 0 };
		GetCursorPos(&point);
		CMenu cMenu;
		cMenu.LoadMenuW(IDR_MENU1);
		CMenu* SubMenu = cMenu.GetSubMenu(0);

		m_RclickProcessId = _tcstoul(m_ListCtrl.GetItemText(pNMItemActivate->iItem, 0), NULL, 10);
		SubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	*pResult = 0;
}


void CMyProcessDialog::OnViewMoudle() {
	// TODO: 在此添加命令处理程序代码
	CMyDiglogProcessMoudle cMydialogProcessMoudle;
	cMydialogProcessMoudle.m_ProcessId = m_RclickProcessId;
	cMydialogProcessMoudle.DoModal();
}


void CMyProcessDialog::OnFinishProcess() {

	// TODO: 在此添加命令处理程序代码

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_RclickProcessId);
	int result;
	if (processHandle != NULL) {
		result = ::TerminateProcess(processHandle, 0);
	}

	if (result == 0) {
		CString value;
		value.Format(_T("结束进程失败,错误码:%d"), GetLastError());
		MessageBox(value);
	}
	else {
		MessageBox(_T("结束进程成功"));
	}
	CloseHandle(processHandle);
}


void CMyProcessDialog::OnClickGetThread() {
	// TODO: 在此添加命令处理程序代码
	CMyDialogViewThread cMyDialogViewThread;
	cMyDialogViewThread.m_ProcessId = m_RclickProcessId;
	cMyDialogViewThread.DoModal();

}


void CMyProcessDialog::OnClikViewHeap() {
	// TODO: 在此添加命令处理程序代码
	CMyDialogViewHeap cMyDialogViewHeap;
	cMyDialogViewHeap.m_ProcessId = m_RclickProcessId;
	cMyDialogViewHeap.DoModal();
}


void CMyProcessDialog::OnLvnItemchangedListProcess(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
DWORD WINAPI ProcessPotectionProc(LPVOID lpThreadParameter) {
	CMyProcessDialog* dialog = (CMyProcessDialog*)lpThreadParameter;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL,dialog->m_RclickProcessId);
	LPVOID memPath = VirtualAllocEx(hProcess, NULL, strlen(processPotectionDllPath), MEM_COMMIT, PAGE_READWRITE);
	DWORD realSize = 0;
	WriteProcessMemory(hProcess, memPath, processPotectionDllPath, strlen(processPotectionDllPath) + 1, &realSize);
	HANDLE thread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)(LoadLibraryA), memPath, 0, 0);
	WaitForSingleObject(thread, -1);

	CString myProcessPID;
	myProcessPID.Format(_T("%d"), GetCurrentProcessId());
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 16, L"ProcessManagerPID");
	PWCHAR pBuf = (PWCHAR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0,16);

	wcscpy_s((PWCHAR)pBuf, 6,myProcessPID);
	while (*pBuf != 0) {
		Sleep(200);
	}
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	return 0;
}

void CMyProcessDialog::OnProcessPotection() {
	// TODO: 在此添加命令处理程序代码
	CreateThread(NULL, NULL, ProcessPotectionProc, (LPVOID)this, NULL, NULL);

}
