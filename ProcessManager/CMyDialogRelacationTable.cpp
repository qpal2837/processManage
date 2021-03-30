// CMyDialogRelacationTable.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogRelacationTable.h"
#include "afxdialogex.h"


// CMyDialogRelacationTable 对话框

IMPLEMENT_DYNAMIC(CMyDialogRelacationTable, CDialogEx)

CMyDialogRelacationTable::CMyDialogRelacationTable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RELACATION, pParent) {

}

CMyDialogRelacationTable::~CMyDialogRelacationTable() {
}

void CMyDialogRelacationTable::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RELACATION_SECTION, m_ListCtrlSection);
	DDX_Control(pDX, IDC_LIST_RELACATION_PIECE, m_ListCtrlPiece);
}


BEGIN_MESSAGE_MAP(CMyDialogRelacationTable, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RELACATION_SECTION, &CMyDialogRelacationTable::OnNMClickListRelacationSection)
END_MESSAGE_MAP()


// CMyDialogRelacationTable 消息处理程序


BOOL CMyDialogRelacationTable::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
		// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlSection.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListCtrlSection.InsertColumn(1, L"Index", LVCFMT_CENTER, 100);
	m_ListCtrlSection.InsertColumn(2, L"Section", LVCFMT_CENTER, 150);
	m_ListCtrlSection.InsertColumn(3, L"RVA", LVCFMT_CENTER, 150);


	m_ListCtrlPiece.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlPiece.InsertColumn(1, L"Index", LVCFMT_CENTER, 50);
	m_ListCtrlPiece.InsertColumn(2, L"RVA", LVCFMT_CENTER, 100);
	m_ListCtrlPiece.InsertColumn(3, L"Offset", LVCFMT_CENTER, 100);
	m_ListCtrlPiece.InsertColumn(4, L"Type", LVCFMT_CENTER, 100);
	m_ListCtrlPiece.InsertColumn(5, L"Far Address", LVCFMT_CENTER, 100);
	m_ListCtrlPiece.InsertColumn(6, L"Data lnterpretation", LVCFMT_CENTER, 300);
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogRelacationTable::GetInfo() {

	GetRelacationTableInfo(sectionInfoArray, sectionLength, pPEstruct);
	CString value;
	for (int i = 0; i < sectionInfoArray.size(); i++) {
		value.Format(_T("%d"), sectionInfoArray[i]->index);
		m_ListCtrlSection.InsertItem(i, value, 0);
		value = sectionInfoArray[i]->section;
		m_ListCtrlSection.SetItemText(i, 1, value);
		value.Format(_T("%08X"), sectionInfoArray[i]->rva);
		m_ListCtrlSection.SetItemText(i, 2, value);
	}
	return VOID();
}

VOID CMyDialogRelacationTable::GetPiece(DWORD index) {
	if (index < 0 || index >= this->sectionInfoArray.size()) {

		return;
	}
	CString value;
	PSectionInfo pse = sectionInfoArray.at(index);

	for (int i = 0; i < pse->pieceInfoArray.size(); i++) {
		value.Format(_T("%d"), pse->pieceInfoArray[i]->index);
		m_ListCtrlPiece.InsertItem(i, value, 0);
		value.Format(_T("%08X"), pse->pieceInfoArray[i]->rva);
		m_ListCtrlPiece.SetItemText(i, 1, value);
		value.Format(_T("%08X"), pse->pieceInfoArray[i]->offset);
		m_ListCtrlPiece.SetItemText(i, 2, value);
		value.Format(_T("%08X"), pse->pieceInfoArray[i]->type);
		m_ListCtrlPiece.SetItemText(i, 3, value);
		value.Format(_T("%08X"), pse->pieceInfoArray[i]->farAddress);
		m_ListCtrlPiece.SetItemText(i, 4, value);

		CString dataInterPrelation;
		for (int j = 0; j < 10; j++) {
			value.Format(_T("%02X"), *(pse->pieceInfoArray[i]->dataInterPrelation + j));
			dataInterPrelation += value;
			dataInterPrelation += " ";
		}
		m_ListCtrlPiece.SetItemText(i, 5, dataInterPrelation);
	}
	return VOID();
}


void CMyDialogRelacationTable::OnNMClickListRelacationSection(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	GetPiece(pNMItemActivate->iItem);
	*pResult = 0;
}
