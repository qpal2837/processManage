// CMyDialogTLS.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogTLS.h"
#include "afxdialogex.h"
// CMyDialogTLS 对话框

IMPLEMENT_DYNAMIC(CMyDialogTLS, CDialogEx)

CMyDialogTLS::CMyDialogTLS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TLS, pParent)
{

}

CMyDialogTLS::~CMyDialogTLS()
{
}

void CMyDialogTLS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialogTLS, CDialogEx)
END_MESSAGE_MAP()


// CMyDialogTLS 消息处理程序


BOOL CMyDialogTLS::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CMyDialogTLS::GetInfo() {
	TLSTableInfo tls;
	GetTLSTableInfo(&tls,pPEstruct);
	CString value;
	value.Format(_T("%08X"),tls.dataStartVA);
	SetDlgItemText(IDC_EDIT_DATASTART_VA,value);
	value.Format(_T("%08X"), tls.dataEndVa);
	SetDlgItemText(IDC_EDIT_DATA_END_VA,value);
	value.Format(_T("%08X"), tls.addressIndex);
	SetDlgItemText(IDC_EDIT_INDEX_VA, value);
	value.Format(_T("%08X"), tls.callFun);
	SetDlgItemText(IDC_EDIT_CALL_VA, value);
	value.Format(_T("%08X"), tls.sizeOfZeroFill);
	SetDlgItemText(IDC_EDIT_ZEROSIZE, value);
	value.Format(_T("%08X"), tls.feature);
	SetDlgItemText(IDC_EDIT_TLS_FEATURE, value);
	return VOID();
}
