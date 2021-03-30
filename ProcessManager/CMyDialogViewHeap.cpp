// CMyDialogViewHeap.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogViewHeap.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyDialogViewHeap 对话框

IMPLEMENT_DYNAMIC(CMyDialogViewHeap, CDialogEx)

CMyDialogViewHeap::CMyDialogViewHeap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VIEW_HEAP, pParent) {

}

CMyDialogViewHeap::~CMyDialogViewHeap() {
}

void CMyDialogViewHeap::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_HEAP, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogViewHeap, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogViewHeap 消息处理程序


BOOL CMyDialogViewHeap::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"堆ID", LVCFMT_CENTER, 180);
	m_ListCtrl.InsertColumn(2, L"进程默认堆", LVCFMT_CENTER, 180);

	GetHeap();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogViewHeap::GetHeap() {
	HANDLE hHeapSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, m_ProcessId);
	HEAPLIST32 heapList32;
	heapList32.dwSize = sizeof(HEAPLIST32);
	TCHAR buf[10];
	int i = 0;
	if (Heap32ListFirst(hHeapSnap, &heapList32)) {
		do {
			_stprintf_s(buf, _T("%d"), heapList32.th32HeapID);
			m_ListCtrl.InsertItem(i, buf, 0);
			m_ListCtrl.SetItemText(i, 1, heapList32.dwFlags?_T("True"):_T("False"));
			i++;
		} while (Heap32ListNext(hHeapSnap,&heapList32));
	}
	CloseHandle(hHeapSnap);
	return VOID();
}
