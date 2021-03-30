// CMyDialogSection.cpp: 实现文件
//
#pragma once
#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogSection.h"
#include "afxdialogex.h"

#pragma comment(lib,"../Debug/PETool.lib") 

// CMyDialogSection 对话框

IMPLEMENT_DYNAMIC(CMyDialogSection, CDialogEx)

CMyDialogSection::CMyDialogSection(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SECTION, pParent) {

}

CMyDialogSection::~CMyDialogSection() {
}

void CMyDialogSection::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECTION, m_ListSection);
}


BEGIN_MESSAGE_MAP(CMyDialogSection, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogSection 消息处理程序


BOOL CMyDialogSection::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListSection.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListSection.InsertColumn(1, L"名称", LVCFMT_CENTER, 100);
	m_ListSection.InsertColumn(2, L"VOffset", LVCFMT_CENTER, 100);
	m_ListSection.InsertColumn(3, L"VSize", LVCFMT_CENTER, 100);
	m_ListSection.InsertColumn(4, L"ROffset", LVCFMT_CENTER, 100);
	m_ListSection.InsertColumn(5, L"RSize", LVCFMT_CENTER, 100);
	m_ListSection.InsertColumn(6, L"标志", LVCFMT_CENTER, 100);
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogSection::GetInfo() {
	PSectionHeadInfo pSectionHeadInfo = NULL;

	GetSectionHeaderInfo(&pSectionHeadInfo, pPEstruct);
	for (int i = 0; i < pPEstruct->fileHead->NumberOfSections; i++) {
		CString value(pSectionHeadInfo[i].sectionName);
		m_ListSection.InsertItem(i, value, 0);
		value.Format(_T("%08X"), pSectionHeadInfo[i].vOffset);
		m_ListSection.SetItemText(i, 1, value);
		value.Format(_T("%08X"), pSectionHeadInfo[i].vSize);
		m_ListSection.SetItemText(i, 2, value);
		value.Format(_T("%08X"), pSectionHeadInfo[i].rOffset);
		m_ListSection.SetItemText(i, 3, value);
		value.Format(_T("%08X"), pSectionHeadInfo[i].rSize);
		m_ListSection.SetItemText(i, 4, value);
		value.Format(_T("%08X"), pSectionHeadInfo[i].Characteristics);
		m_ListSection.SetItemText(i, 5, value);
	}
	return VOID();
}
