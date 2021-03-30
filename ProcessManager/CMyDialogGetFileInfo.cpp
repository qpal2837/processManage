// CMyDialogGetFileInfo.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogGetFileInfo.h"
#include "afxdialogex.h"
#include "CMyDialogChoiceFile.h"

// CMyDialogGetFileInfo 对话框

IMPLEMENT_DYNAMIC(CMyDialogGetFileInfo, CDialogEx)

CMyDialogGetFileInfo::CMyDialogGetFileInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FILE_INFO, pParent) {

}

CMyDialogGetFileInfo::~CMyDialogGetFileInfo() {
}

void CMyDialogGetFileInfo::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditFilePath);
	DDX_Control(pDX, IDC_EDIT2, m_EditFileInfo);
	DDX_Control(pDX, IDC_EDIT3, m_EditDelete);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ButtonDelete);
}


BEGIN_MESSAGE_MAP(CMyDialogGetFileInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CHOICE_FILE, &CMyDialogGetFileInfo::OnBnClickedButtonOpenChoiceFile)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMyDialogGetFileInfo::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CMyDialogGetFileInfo 消息处理程序


BOOL CMyDialogGetFileInfo::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ClearSuffix.push_back(_T(".obj"));
	m_ClearSuffix.push_back(_T(".tlog"));
	m_ClearSuffix.push_back(_T(".lastbuildstate"));
	m_ClearSuffix.push_back(_T(".idb"));
	m_ClearSuffix.push_back(_T(".pdb"));
	m_ClearSuffix.push_back(_T(".pch"));
	m_ClearSuffix.push_back(_T(".res"));
	m_ClearSuffix.push_back(_T(".ilk"));
	m_ClearSuffix.push_back(_T(".exe"));
	m_ClearSuffix.push_back(_T(".sdf"));
	m_ClearSuffix.push_back(_T(".ipch"));
	m_ClearSuffix.push_back(_T(".log"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMyDialogGetFileInfo::OnBnClickedButtonOpenChoiceFile() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogChoiceFile choiceFileDialog;
	choiceFileDialog.m_SourseFlag = 1;
	choiceFileDialog.m_CmyDialogGetFileInfo = this;
	choiceFileDialog.DoModal();


}

VOID CMyDialogGetFileInfo::SetChoiceFileEdit() {
	m_EditFilePath.SetWindowTextW(m_FilePath);
	GetFileInfoByPath();
	return VOID();
}
VOID CMyDialogGetFileInfo::MyGetFileSize(CString path, DWORD& fileSize, DWORD& deleteFileSize) {
	CString tempPath = _T("");
	CString perfectTempPath = _T("");
	tempPath = path;
	tempPath += "\\*";
	WIN32_FIND_DATA  wfd = {};
	HANDLE hFile = FindFirstFile(tempPath, &wfd);
	do {
		if (StrCmp(wfd.cFileName, L".") == 0 || StrCmp(wfd.cFileName, L"..") == 0) {
			continue;
		}
		perfectTempPath = path;
		perfectTempPath += "\\";
		perfectTempPath += wfd.cFileName;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			MyGetFileSize(perfectTempPath, fileSize, deleteFileSize);
		}
		else {
			int value = perfectTempPath.ReverseFind('.');
			if (value != -1) {
				CString sub = perfectTempPath;
				sub.Delete(0,value);
				for (int i = 0; i < m_ClearSuffix.size(); i++) {
					if (sub == m_ClearSuffix[i]) {
						m_DeleteFilePath.push_back(perfectTempPath);
						deleteFileSize+= (wfd.nFileSizeHigh * (0 + 1) + wfd.nFileSizeLow);
					}
				}
			}
				fileSize += (wfd.nFileSizeHigh * (0 + 1) + wfd.nFileSizeLow);
		}
	} while (FindNextFile(hFile, &wfd));
}
VOID CMyDialogGetFileInfo::GetFileInfoByPath() {
	m_DeleteFilePath.clear();
	WIN32_FIND_DATA  wfd = {};
	HANDLE hFindFile = FindFirstFile(m_FilePath, &wfd);

	DWORD fileSize = 0;
	DWORD deleteFileSize = 0;
	FILETIME createTime;
	FILETIME updateTime;
	SYSTEMTIME createTimeSysTime;
	SYSTEMTIME updateTimeSysTime;
	CString fileInfo;
	FileTimeToLocalFileTime(&wfd.ftCreationTime, &createTime);
	FileTimeToSystemTime(&createTime, &createTimeSysTime);

	FileTimeToLocalFileTime(&wfd.ftLastWriteTime, &updateTime);
	FileTimeToSystemTime(&updateTime, &updateTimeSysTime);

	if (hFindFile == INVALID_HANDLE_VALUE) {
		CString value;
		value.Format(_T("文件获取错误,错误码:%d"), GetLastError());
	}

	MyGetFileSize(m_FilePath, fileSize, deleteFileSize);
	fileInfo.Format(_T("创建时间:%d年%d月%d日%d时%d分\r\n修改时间:%d年%d月%d日%d时%d分\r\n文件大小:%d字节"),
		createTimeSysTime.wYear,
		createTimeSysTime.wMonth, createTimeSysTime.wDay, createTimeSysTime.wHour, createTimeSysTime.wMinute,
		updateTimeSysTime.wYear,
		updateTimeSysTime.wMonth, updateTimeSysTime.wDay, updateTimeSysTime.wHour,
		updateTimeSysTime.wMinute,
		fileSize
	);
	CString deleteFileInfo;
	CString value;
	for (int i = 0; i < m_DeleteFilePath.size(); i++) {
		value.Format(_T("文件:%s\r\n"),m_DeleteFilePath[i]);
		deleteFileInfo += value;
	}

	value.Format(_T("共:%d字节\r\n"),deleteFileSize);
	deleteFileInfo += value;
	m_EditFileInfo.SetWindowTextW(fileInfo);
	m_EditDelete.SetWindowTextW(deleteFileInfo);
	m_ButtonDelete.EnableWindow(TRUE);
	return VOID();
}



void CMyDialogGetFileInfo::OnBnClickedButtonDelete() {
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_DeleteFilePath.size(); i++) {
		DeleteFile(m_DeleteFilePath[i]);
	}
	MessageBox(_T("删除成功"));
}
