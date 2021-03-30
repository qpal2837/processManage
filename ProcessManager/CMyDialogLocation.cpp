// CMyDialogLocation.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogLocation.h"
#include "afxdialogex.h"


// CMyDialogLocation 对话框

IMPLEMENT_DYNAMIC(CMyDialogLocation, CDialogEx)

CMyDialogLocation::CMyDialogLocation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COUNT_LOCATION, pParent) {

}

CMyDialogLocation::~CMyDialogLocation() {
}

void CMyDialogLocation::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_VA, m_ButtonVA);
	DDX_Control(pDX, IDC_BUTTON_RVA, m_ButtonRVA);
	DDX_Control(pDX, IDC_BUTTON_FOA, m_ButtonFOA);
	DDX_Control(pDX, IDC_EDIT_VA, m_EditVA);
	DDX_Control(pDX, IDC_EDIT_RVA, m_EditRVA);
	DDX_Control(pDX, IDC_EDIT_FOA, m_EditFOA);
	DDX_Control(pDX, IDC_EDIT_LOCATION_SECTION, m_EditSection);
	DDX_Control(pDX, IDC_EDIT_LOCATION_BYTE, m_EditByte);
}


BEGIN_MESSAGE_MAP(CMyDialogLocation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VA, &CMyDialogLocation::OnBnClickedButtonVa)
	ON_BN_CLICKED(IDC_BUTTON_FOA, &CMyDialogLocation::OnBnClickedButtonFoa)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION_ENTER, &CMyDialogLocation::OnBnClickedButtonLocationEnter)
	ON_BN_CLICKED(IDC_BUTTON_RVA, &CMyDialogLocation::OnBnClickedButtonRva)
END_MESSAGE_MAP()


// CMyDialogLocation 消息处理程序


void CMyDialogLocation::OnBnClickedButtonVa() {
	// TODO: 在此添加控件通知处理程序代码
	m_EditRVA.SetReadOnly(TRUE);
	m_EditFOA.SetReadOnly(TRUE);
	m_EditVA.SetReadOnly(FALSE);

}


void CMyDialogLocation::OnBnClickedButtonFoa() {
	// TODO: 在此添加控件通知处理程序代码
	m_EditRVA.SetReadOnly(TRUE);
	m_EditVA.SetReadOnly(TRUE);
	m_EditFOA.SetReadOnly(FALSE);
}

void CMyDialogLocation::OnBnClickedButtonRva() {
	// TODO: 在此添加控件通知处理程序代码
	m_EditVA.SetReadOnly(TRUE);
	m_EditFOA.SetReadOnly(TRUE);
	m_EditRVA.SetReadOnly(FALSE);
}
void CMyDialogLocation::OnBnClickedButtonLocationEnter() {
	// TODO: 在此添加控件通知处理程序代码
	LocationInfo plc = {};
	CString valueB;
	if (!(GetWindowLong(m_EditFOA.m_hWnd, GWL_STYLE) & ES_READONLY)) {
		GetDlgItemText(IDC_EDIT_FOA, valueB);
		DWORD dwValue = _tcstoul(valueB, NULL, 16);
		plc.foa = dwValue;
		CountLocationInfo(&plc, LocationFlagEnum::FOA, pPEstruct);
	}
	if (!(GetWindowLong(m_EditVA.m_hWnd, GWL_STYLE) & ES_READONLY)) {
		GetDlgItemText(IDC_EDIT_VA, valueB);
		DWORD dwValue = _tcstoul(valueB, NULL, 16);
		plc.va = dwValue;
		CountLocationInfo(&plc, LocationFlagEnum::VA, pPEstruct);
	}
	if (!(GetWindowLong(m_EditRVA.m_hWnd, GWL_STYLE) & ES_READONLY)) {
		GetDlgItemText(IDC_EDIT_RVA, valueB);
		DWORD dwValue = _tcstoul(valueB, NULL, 16);
		plc.rva = dwValue;
		CountLocationInfo(&plc, LocationFlagEnum::RVA, pPEstruct);
	}
	CString value;
	value.Format(_T("%08X"), plc.va);
	SetDlgItemTextW(IDC_EDIT_VA, value);
	value.Format(_T("%08X"), plc.rva);
	SetDlgItemTextW(IDC_EDIT_RVA, value);
	value.Format(_T("%08X"), plc.foa);
	SetDlgItemTextW(IDC_EDIT_FOA, value);

	value = (plc.section);
	SetDlgItemText(IDC_EDIT_LOCATION_SECTION, value);

	CString dataInterPrelation;
	for (int j = 0; j < 10; j++) {
		value.Format(_T("%02X"), *(plc.dataInterPrelation + j));
		dataInterPrelation += value;
		dataInterPrelation += " ";
	}
	SetDlgItemText(IDC_EDIT_LOCATION_BYTE, dataInterPrelation);
}



