// CMyDialogResource.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogResource.h"
#include "afxdialogex.h"


// CMyDialogResource 对话框

IMPLEMENT_DYNAMIC(CMyDialogResource, CDialogEx)

CMyDialogResource::CMyDialogResource(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent) {

}

CMyDialogResource::~CMyDialogResource() {
}


void CMyDialogResource::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_RE, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogResource, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_RE, &CMyDialogResource::OnTvnSelchangedTreeRe)
END_MESSAGE_MAP()


// CMyDialogResource 消息处理程序


BOOL CMyDialogResource::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogResource::GetInfo() {
	GetResourceInfo(&resourceInfo, pPEstruct);
	SetDlgItemInt(IDC_EDIT_RENAME, resourceInfo.rootNameCount);
	SetDlgItemInt(IDC_EDIT_RE_ID, resourceInfo.rootIdCount);
	for (int i = 0; i < resourceInfo.parentArray.size(); i++) {
		CString value;
		if (resourceInfo.parentArray[i].id == -1) {
			value = resourceInfo.parentArray[i].name;
		}
		else {
			value.Format(_T("%d"), resourceInfo.parentArray[i].id);
		}
		HTREEITEM item = m_TreeCtrl.InsertItem(value);
		for (int j = 0; j < resourceInfo.parentArray[i].childArray.size(); j++) {
			CString valueB;
			if (resourceInfo.parentArray[i].childArray[j].id == -1) {
				valueB = resourceInfo.parentArray[i].childArray[j].name;
			}
			else {
				valueB.Format(_T("%d"), resourceInfo.parentArray[i].childArray[j].id);
			}
			m_TreeCtrl.InsertItem(valueB, item);
		}
	}
	return VOID();
}

void CMyDialogResource::OnTvnSelchangedTreeRe(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hitem = pNMTreeView->itemNew.hItem;
	CString selectValue = m_TreeCtrl.GetItemText(hitem);
	for (int i = 0; i < resourceInfo.parentArray.size(); i++) {
		CString idValue;
		idValue.Format(_T("%d"), resourceInfo.parentArray[i].id);
		if (StrCmp(resourceInfo.parentArray[i].name, selectValue) == 0 || StrCmp(idValue, selectValue) == 0) {
			SetDlgItemInt(IDC_EDIT_RE_CH_NAME, resourceInfo.parentArray[i].nameItem);
			SetDlgItemInt(IDC_EDIT_RE_CH_ID, resourceInfo.parentArray[i].idItem);
			break;
		}
		for (int j = 0; j < resourceInfo.parentArray[i].childArray.size(); j++) {
			CString idValueB;
			idValueB.Format(_T("%d"), resourceInfo.parentArray[i].childArray[j].id);
			if (StrCmp(resourceInfo.parentArray[i].childArray[j].name, selectValue) == 0 || StrCmp(idValueB, selectValue) == 0) {
				CString tempValue;
				tempValue.Format(_T("%08X"), resourceInfo.parentArray[i].childArray[j].foa);
				SetDlgItemText(IDC_EDIT_RE_FOA, tempValue);
				tempValue.Format(_T("%08X"), resourceInfo.parentArray[i].childArray[j].rva);
				SetDlgItemText(IDC_EDIT_RE_RVA, tempValue);
				break;
			}
		}
	}
	*pResult = 0;
}
