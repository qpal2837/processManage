// CMyTabCtrl.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyTabCtrl.h"
#include "CMyDialogPE.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl() {

}

CMyTabCtrl::~CMyTabCtrl() {
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTabCtrl::OnTcnSelchange)
	ON_WM_SIZE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序






// 添加 1 个指定选项卡标题并和对话框产生关联
VOID CMyTabCtrl::InsertTabItem(int index, LPCWSTR TabName, CDialog* Dialog, INT Id) {
	// 1. 添加标题到指定的位置
	this->InsertItem(index, TabName);

	// 2. 将对话框创建起来并关联到选项卡控件
	Dialog->Create(Id);
	m_Dlgs.push_back(Dialog);

	// 3. 移动对话框的位置
	CRect TabRect;
	this->GetClientRect(TabRect);
	TabRect.DeflateRect(10, 10, 70, 70);
	Dialog->MoveWindow(TabRect);
}

// 显示指定的选项卡，并隐藏其它选项卡
VOID CMyTabCtrl::ShowTab(int index) {
	for (size_t i = 0; i < m_Dlgs.size(); ++i) {
		m_Dlgs[i]->ShowWindow(index == i ? SW_SHOWNORMAL : SW_HIDE);
	}
}


void CMyTabCtrl::OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult) {
	ShowTab(GetCurSel());
	*pResult = 0;
}


// 通过变参函数让目标选项卡添加多个对话框(count 表示组数(名称+指针+id))
VOID CMyTabCtrl::InsertTabItems(int count, ...) {
	va_list arg_point;
	va_start(arg_point, count);

	for (int i = 0; i < count; ++i) {
		// 0. 获取到每一组的内容
		LPCWSTR TabName = va_arg(arg_point, LPCWSTR);
		CDialog* Dlg = va_arg(arg_point, CDialog*);
		INT DlgId = va_arg(arg_point, INT);
		this->InsertItem(i, TabName);
		Dlg->Create(DlgId);
		m_Dlgs.push_back(Dlg);

		CRect TabRect;
		this->GetClientRect(TabRect);
		TabRect.DeflateRect(45, 45, 31, 20);
		Dlg->MoveWindow(TabRect);
	}

	va_end(arg_point);
}

//void CMyTabCtrl::OnSize(UINT nType, int cx, int cy) {
//	CTabCtrl::OnSize(nType, cx, cy);
//
//	// TODO: 在此处添加消息处理程序代码
//}


void CMyTabCtrl::OnDropFiles(HDROP hDropInfo) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMyDialogPE* dialogPe = (CMyDialogPE*)m_Dlgs[3];
	DragQueryFileA(hDropInfo, 0, dialogPe->filePath, MAX_PATH);
	dialogPe->InitPEInfo();
	CTabCtrl::OnDropFiles(hDropInfo);
}
