// CMyDialogPE.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogPE.h"
#include "afxdialogex.h"
#include "CMyDialogDirectory.h"
#include "CMyDialogLocation.h"
// CMyDialogPE 对话框

IMPLEMENT_DYNAMIC(CMyDialogPE, CDialogEx)

CMyDialogPE::CMyDialogPE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PE, pParent) {

}

CMyDialogPE::~CMyDialogPE() {
}

void CMyDialogPE::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SECTION, m_ButtonSection);
	DDX_Control(pDX, IDC_BUTTON_DIRECRYTION, m_ButtonDirecty);
	DDX_Control(pDX, IDC_BUTTON_LOCATION, m_ButtonLocation);
}


BEGIN_MESSAGE_MAP(CMyDialogPE, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_SECTION, &CMyDialogPE::OnBnClickedButtonSection)
	ON_BN_CLICKED(IDC_BUTTON_DIRECRYTION, &CMyDialogPE::OnBnClickedButtonDirecrytion)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION, &CMyDialogPE::OnBnClickedButtonLocation)
END_MESSAGE_MAP()


// CMyDialogPE 消息处理程序


BOOL CMyDialogPE::OnInitDialog() {
	CDialogEx::OnInitDialog();
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	// TODO:  在此添加额外的初始化
	pPEstruct = (PPEstruct)malloc(sizeof(PEStruct));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMyDialogPE::OnDropFiles(HDROP hDropInfo) {
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnDropFiles(hDropInfo);
}

VOID CMyDialogPE::InitPEInfo() {
	DWORD ret = LoadPeFile(filePath, pPEstruct);
	if (ret == ResultEnum::NO_PE_FILE) {
		MessageBox(_T("不是PE文件"), 0, 0);
		return;
	}
	PPeInfo pPeInfo = NULL;
	GetPEInfo(&pPeInfo, pPEstruct);
	CString value;
	value.Format(_T("%08x"), pPeInfo->entryPoint);
	SetDlgItemText(IDC_EDIT_ENTRY_POINT, value);

	value.Format(_T("%08x"), pPeInfo->imageBase);
	SetDlgItemText(IDC_EDIT_IMAGE_BASE, value);

	value.Format(_T("%08x"), pPeInfo->imageSize);
	SetDlgItemText(IDC_EDIT_IMAGE_SIZE, value);

	value.Format(_T("%08x"), pPeInfo->codeBase);
	SetDlgItemText(IDC_EDIT_CODE_BASE, value);

	value.Format(_T("%08X"), pPeInfo->dataBase);
	SetDlgItemText(IDC_EDIT_DATA_BASE, value);

	value.Format(_T("%08X"), pPeInfo->pieceAlignment);
	SetDlgItemText(IDC_EDIT_PIECE_ALIGNMENT, value);

	value.Format(_T("%08X"), pPeInfo->fileAlignment);
	SetDlgItemText(IDC_EDIT_FILE_ALIGNMENT, value);

	value.Format(_T("%08X"), pPeInfo->flagWord);
	SetDlgItemText(IDC_EDIT_FLAG_WORD, value);

	value.Format(_T("%08X"), pPeInfo->childSystem);
	SetDlgItemText(IDC_EDIT_CHILD_SYSTEM, value);

	value.Format(_T("%08X"), pPeInfo->sectionCount);
	SetDlgItemText(IDC_EDIT_SECTION_COUNT, value);

	value.Format(_T("%08X"), pPeInfo->timeStamp);
	SetDlgItemText(IDC_EDIT_TIMESTAMP, value);

	value.Format(_T("%08X"), pPeInfo->headSize);
	SetDlgItemText(IDC_EDIT_HEAD_SIZE, value);

	value.Format(_T("%08X"), pPeInfo->featureValue);
	SetDlgItemText(IDC_EDIT_FEATURE_VALUE, value);

	value.Format(_T("%08X"), pPeInfo->checkSum);
	SetDlgItemText(IDC_EDIT_CHECK_SUM, value);

	value.Format(_T("%08X"), pPeInfo->OptionalHeadSize);
	SetDlgItemText(IDC_EDIT_OPTIONALHEAD_SIZE, value);

	value.Format(_T("%08X"), pPeInfo->NumberOfRvaAndSizes);
	SetDlgItemText(IDC_EDIT_NUMBER_OF_RVA, value);


	m_ButtonSection.EnableWindow(TRUE);
	m_ButtonDirecty.EnableWindow(TRUE);
	m_ButtonLocation.EnableWindow(TRUE);

	return VOID();
}



void CMyDialogPE::OnBnClickedButtonSection() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogSection cMyDialogSection;
	cMyDialogSection.pPEstruct = pPEstruct;
	cMyDialogSection.DoModal();
}


void CMyDialogPE::OnBnClickedButtonDirecrytion() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogDirectory cMydialogDirectory;
	cMydialogDirectory.pPEstruct = this->pPEstruct;
	cMydialogDirectory.DoModal();
}


void CMyDialogPE::OnBnClickedButtonLocation() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogLocation cMyDialogLocation;
	cMyDialogLocation.pPEstruct = this->pPEstruct;
	cMyDialogLocation.DoModal();
}
