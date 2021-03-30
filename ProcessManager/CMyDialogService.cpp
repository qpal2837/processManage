// CMyDialogService.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogService.h"
#include "afxdialogex.h"
#include <winsvc.h>

// CMyDialogService 对话框

IMPLEMENT_DYNAMIC(CMyDialogService, CDialogEx)

CMyDialogService::CMyDialogService(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SERVICE, pParent) {

}

CMyDialogService::~CMyDialogService() {
}

void CMyDialogService::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVICE, m_ListCtrlService);
}


BEGIN_MESSAGE_MAP(CMyDialogService, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SERVICE, &CMyDialogService::OnLvnItemchangedListService)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SERVICE, &CMyDialogService::OnNMRClickListService)
	ON_COMMAND(ID_32778, &CMyDialogService::OnStartService)
	ON_COMMAND(ID_32779, &CMyDialogService::OnCloseService)
END_MESSAGE_MAP()


// CMyDialogService 消息处理程序


void CMyDialogService::OnLvnItemchangedListService(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
VOID GetServiceInfo(LPVOID lpThreadParameter) {
	DWORD dwServiceNum = 0;
	DWORD dwSize = 0;
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		NULL, 0, &dwSize, &dwServiceNum, NULL, NULL);
	LPENUM_SERVICE_STATUS_PROCESS pEnumService = (LPENUM_SERVICE_STATUS_PROCESS)new char[dwSize];
	bool bStatus = FALSE;
	bStatus = EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		(PBYTE)pEnumService, dwSize, &dwSize, &dwServiceNum, NULL, NULL);
	CMyDialogService* cMydialogService = (CMyDialogService*)lpThreadParameter;
	CString value;
	int n = cMydialogService->m_ListCtrlService.GetTopIndex();
	int nLast = n + cMydialogService->m_ListCtrlService.GetCountPerPage();
	cMydialogService->m_ListCtrlService.DeleteAllItems();
	for (DWORD i = 0; i < dwServiceNum; i++) {
		cMydialogService->m_ListCtrlService.InsertItem(i, pEnumService[i].lpServiceName, 0);
		value.Format(_T("%d"), pEnumService[i].ServiceStatusProcess.dwProcessId);
		cMydialogService->m_ListCtrlService.SetItemText(i, 1, value);
		cMydialogService->m_ListCtrlService.SetItemText(i, 2, pEnumService[i].lpDisplayName);
		cMydialogService->m_ListCtrlService.SetItemText(i, 3,
			pEnumService[i].ServiceStatusProcess.dwCurrentState == SERVICE_STOPPED ? _T("已停止") : _T("正在运行"));
		SC_HANDLE hService = OpenService(hSCM, pEnumService[i].lpServiceName, SERVICE_QUERY_CONFIG);
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		LPQUERY_SERVICE_CONFIG pServiceConfig = (LPQUERY_SERVICE_CONFIG)new char[dwSize];
		QueryServiceConfig(hService, pServiceConfig, dwSize, &dwSize);
		cMydialogService->m_ListCtrlService.SetItemText(i, 4, pServiceConfig->lpLoadOrderGroup);
	}
	cMydialogService->m_ListCtrlService.EnsureVisible(nLast - 1, TRUE);

}
DWORD WINAPI GetServiceProc(LPVOID lpThreadParameter) {
	while (true) {
		GetServiceInfo(lpThreadParameter);
		Sleep(3000);
	}

}


BOOL CMyDialogService::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlService.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlService.InsertColumn(1, L"名称", LVCFMT_CENTER, 200);
	m_ListCtrlService.InsertColumn(2, L"PID", LVCFMT_CENTER, 80);
	m_ListCtrlService.InsertColumn(3, L"描述", LVCFMT_CENTER, 250);
	m_ListCtrlService.InsertColumn(4, L"状态", LVCFMT_CENTER, 100);
	m_ListCtrlService.InsertColumn(5, L"组", LVCFMT_CENTER, 150);



	CreateThread(NULL, NULL, GetServiceProc, (LPVOID)this, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMyDialogService::OnNMRClickListService(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1) {
		POINT point = { 0 };
		GetCursorPos(&point);
		CMenu cMenu;
		cMenu.LoadMenuW(IDR_MENU3);
		CMenu* SubMenu = cMenu.GetSubMenu(0);

		m_RlickServiceName = m_ListCtrlService.GetItemText(pNMItemActivate->iItem, 0);
		SubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	*pResult = 0;
}


void CMyDialogService::OnStartService() {
	// TODO: 在此添加命令处理程序代码
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = OpenService(hSCM, m_RlickServiceName, SC_MANAGER_ALL_ACCESS);
	DWORD ret = StartService(hService, NULL, NULL);
	if (ret != 0) {
		MessageBox(_T("启动成功!"));
	}
	else {
		MessageBox(_T("启动失败!"));
	}

}


void CMyDialogService::OnCloseService() {
	// TODO: 在此添加命令处理程序代码
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService = OpenService(hSCM, m_RlickServiceName, SC_MANAGER_ALL_ACCESS);
	SERVICE_STATUS status = { 0 };
	DWORD ret = ControlService(hService, SERVICE_CONTROL_STOP, &status);
	if (ret != 0) {
		MessageBox(_T("通知关闭成功!"));
	}
	else {
		MessageBox(_T("通知关闭失败!"));
	}
}
