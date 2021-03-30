// CMyDialogViewThread.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogViewThread.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyDialogViewThread 对话框

IMPLEMENT_DYNAMIC(CMyDialogViewThread, CDialogEx)

CMyDialogViewThread::CMyDialogViewThread(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VIEW_THREAD, pParent) {

}

CMyDialogViewThread::~CMyDialogViewThread() {
}

void CMyDialogViewThread::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_THREAD, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogViewThread, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_VIEW_THREAD, &CMyDialogViewThread::OnNMRClickListViewThread)
	ON_COMMAND(ID_32774, &CMyDialogViewThread::OnClickSuspendThread)
	ON_COMMAND(ID_32775, &CMyDialogViewThread::OnClickResumeThread)
	ON_COMMAND(ID_32776, &CMyDialogViewThread::OnClickFinishThread)
END_MESSAGE_MAP()


// CMyDialogViewThread 消息处理程序


BOOL CMyDialogViewThread::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		// TODO:  在此添加额外的初始化
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"线程ID", LVCFMT_CENTER, 180);
	m_ListCtrl.InsertColumn(2, L"线程优先级", LVCFMT_CENTER, 180);

	GetThread();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogViewThread::GetThread() {
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	THREADENTRY32 stcTe32;
	stcTe32.dwSize = sizeof(THREADENTRY32);
	Thread32First(hThreadSnap, &stcTe32);
	TCHAR buf[10];
	int i = 0;
	do {
		if (stcTe32.th32OwnerProcessID == m_ProcessId) {

			_stprintf_s(buf, _T("%d"), stcTe32.th32ThreadID);
			m_ListCtrl.InsertItem(i, buf, 0);
			_stprintf_s(buf, _T("%d"), stcTe32.tpBasePri);
			m_ListCtrl.SetItemText(i, 1, buf);
			i++;
		}
	} while (Thread32Next(hThreadSnap, &stcTe32));


}
void CMyDialogViewThread::OnNMRClickListViewThread(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1) {
		POINT point = { 0 };
		GetCursorPos(&point);
		CMenu cMenu;
		cMenu.LoadMenuW(IDR_MENU2);
		CMenu* SubMenu = cMenu.GetSubMenu(0);

		m_RClickThreadId = _tcstoul(m_ListCtrl.GetItemText(pNMItemActivate->iItem, 0), NULL, 10);
		SubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	*pResult = 0;
}


void CMyDialogViewThread::OnClickSuspendThread() {
	// TODO: 在此添加命令处理程序代码
	HANDLE thread = OpenThread(THREAD_ALL_ACCESS, FALSE, m_RClickThreadId);
	if (thread == NULL) {
		MessageBox(_T("此线程现在不存在"));
		return;
	}
	int result = SuspendThread(thread);
	if (result == -1) {
		CString value;
		value.Format(_T("线程挂起失败,错误码:%d"), GetLastError);
		MessageBox(value);
	}
	else {
		MessageBox(_T("线程挂起成功"));
	}

}


void CMyDialogViewThread::OnClickResumeThread() {
	// TODO: 在此添加命令处理程序代码
	HANDLE thread = OpenThread(THREAD_ALL_ACCESS, FALSE, m_RClickThreadId);
	if (thread == NULL) {
		MessageBox(_T("此线程现在不存在"));
		return;
	}
	int result = ResumeThread(thread);
	if (result == -1) {
		CString value;
		value.Format(_T("线程恢复失败,错误码:%d"), GetLastError);
		MessageBox(value);
	}
	else {
		MessageBox(_T("线程恢复成功"));
	}
}

DWORD WINAPI FinishThreadProc(LPVOID lpThreadParameter) {
	CMyDialogViewThread* cMyDialogViewThread = (CMyDialogViewThread*)lpThreadParameter;
	HANDLE thread = OpenThread(THREAD_ALL_ACCESS, FALSE, cMyDialogViewThread->m_RClickThreadId);
	if (thread == NULL) {
		cMyDialogViewThread->MessageBox(_T("线程不存在"));
		return 0;
	}
	TerminateThread(thread, 1);
	DWORD value = WaitForSingleObject(thread, 1000);
	if (value == WAIT_TIMEOUT) {
		CString value;
		value.Format(_T("线程结束失败,错误码:%d"), GetLastError);
		cMyDialogViewThread->MessageBox(value);
	}
	else {
		cMyDialogViewThread->MessageBox(_T("线程结束成功"));
	}
	return 0;

}
void CMyDialogViewThread::OnClickFinishThread() {
	// TODO: 在此添加命令处理程序代码
	CreateThread(NULL, NULL, FinishThreadProc, (LPVOID)this, NULL, NULL);

}
