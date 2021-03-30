// CMyDiglogProcessMoudle.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDiglogProcessMoudle.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

// CMyDiglogProcessMoudle 对话框

IMPLEMENT_DYNAMIC(CMyDiglogProcessMoudle, CDialogEx)

CMyDiglogProcessMoudle::CMyDiglogProcessMoudle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS_MOUDLE, pParent) {

}

CMyDiglogProcessMoudle::~CMyDiglogProcessMoudle() {
}

void CMyDiglogProcessMoudle::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS_MOUDLE, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDiglogProcessMoudle, CDialogEx)
END_MESSAGE_MAP()


// CMyDiglogProcessMoudle 消息处理程序


BOOL CMyDiglogProcessMoudle::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"PID", LVCFMT_CENTER, 80);
	m_ListCtrl.InsertColumn(2, L"模块名称", LVCFMT_CENTER, 180);
	m_ListCtrl.InsertColumn(3, L"模块路径", LVCFMT_CENTER, 180);
	m_ListCtrl.InsertColumn(3, L"模块基址", LVCFMT_CENTER, 80);
	GetMoudlbe();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDiglogProcessMoudle::GetMoudlbe() {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE, //创建了一个模块快照
		m_ProcessId               //模块属于进程，这里需提供进程ID
	);
	//2 遍历快照
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	BOOL bSucess = Module32First(hSnapshot, &me32);
	if (bSucess == true) {
		int i = 0;
		TCHAR buf[10];
		do {
			_stprintf_s(buf, _T("%d"), me32.th32ProcessID);
			m_ListCtrl.InsertItem(i, buf, 0);
			m_ListCtrl.SetItemText(i, 1, me32.szModule);
			m_ListCtrl.SetItemText(i, 2, me32.szExePath);
			_stprintf_s(buf,_T("%x"), me32.modBaseAddr);
			m_ListCtrl.SetItemText(i, 3,buf);
			i++;
		} while (Module32Next(hSnapshot, &me32));
	}
	CloseHandle(hSnapshot);
}
