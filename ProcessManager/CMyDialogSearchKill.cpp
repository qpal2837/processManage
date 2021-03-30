// CMyDialogSearchKill.cpp: 实现文件
//

#include "pch.h"
#include "ProcessManager.h"
#include "CMyDialogSearchKill.h"
#include "afxdialogex.h"
#include "CMyDialogChoiceFile.h"
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <TlHelp32.h>
#include <fstream>
#include "MyStruct.h"
#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")

CString md5FilePath = _T(".//MD5//MD5数据.txt");
string blackProcess = ".//进程黑名单//黑名单.txt";
SOCKET sock = NULL;
// CMyDialogSearchKill 对话框
DWORD cloudKillCount = 0;
CRITICAL_SECTION g_cs = {};
HANDLE hSemaphore = NULL;
DWORD filePathIndex = 0;
IMPLEMENT_DYNAMIC(CMyDialogSearchKill, CDialogEx)

CMyDialogSearchKill::CMyDialogSearchKill(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCHKILL, pParent) {

}

CMyDialogSearchKill::~CMyDialogSearchKill() {
}

void CMyDialogSearchKill::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SK_FILE, m_EditFilePath);
	DDX_Control(pDX, IDC_BUTTON_LOCALSK, m_ButtonLocal);
	DDX_Control(pDX, IDC_BUTTON_BLACKSK, m_ButtonBlack);
	DDX_Control(pDX, IDC_BUTTON_RMSK, m_ButtonRm);
	DDX_Control(pDX, IDC_LIST_SCANFSK, m_ListSanf);
	DDX_Control(pDX, IDC_BUTTON_SK_CLOSEP, m_ButtonCloseP);
	DDX_Control(pDX, IDC_BUTTON_SK_KILLLOCAL, m_ButtonDeLocal);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_EditBrowseCtrl);
	DDX_Control(pDX, IDC_BUTTON_SK_UP, m_ButtonUp);
	DDX_Control(pDX, IDC_BUTTON_RMSK3, m_ButtonContinue);
	DDX_Control(pDX, IDC_BUTTON_RMSK2, m_ButtonPause);
}

VOID CMyDialogSearchKill::SetChoiceFileEdit() {
	m_EditFilePath.SetWindowTextW(m_FilePath);
	m_ButtonLocal.EnableWindow(TRUE);
	m_ButtonBlack.EnableWindow(TRUE);
	m_ButtonRm.EnableWindow(TRUE);
	return VOID();
}


BEGIN_MESSAGE_MAP(CMyDialogSearchKill, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SK_CHOICEFILE, &CMyDialogSearchKill::OnBnClickedButtonSkChoicefile)
	ON_BN_CLICKED(IDC_BUTTON_LOCALSK, &CMyDialogSearchKill::OnBnClickedButtonLocalsk)
	ON_BN_CLICKED(IDC_BUTTON_BLACKSK, &CMyDialogSearchKill::OnBnClickedButtonBlacksk)
	ON_BN_CLICKED(IDC_BUTTON_SK_CLOSEP, &CMyDialogSearchKill::OnBnClickedButtonSkClosep)
	ON_BN_CLICKED(IDC_BUTTON_SK_KILLLOCAL, &CMyDialogSearchKill::OnBnClickedButtonSkKilllocal)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CMyDialogSearchKill::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BUTTON_SK_UP, &CMyDialogSearchKill::OnBnClickedButtonSkUp)
	ON_BN_CLICKED(IDC_BUTTON_RMSK, &CMyDialogSearchKill::OnBnClickedButtonRmsk)
	ON_BN_CLICKED(IDC_BUTTON_RMSK2, &CMyDialogSearchKill::OnBnClickedButtonRmsk2)
	ON_BN_CLICKED(IDC_BUTTON_RMSK3, &CMyDialogSearchKill::OnBnClickedButtonRmsk3)
END_MESSAGE_MAP()


// CMyDialogSearchKill 消息处理程序


BOOL CMyDialogSearchKill::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListSanf.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListSanf.InsertColumn(1, L"文件位置/黑名单进程", LVCFMT_CENTER, 300);
	m_ListSanf.InsertColumn(2, L"文件MD5/PID", LVCFMT_CENTER, 250);
	m_ListSanf.InsertColumn(3, L"MD5校验结果", LVCFMT_CENTER, 120);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

int CMyDialogSearchKill::MD5Encrypt(const void* data, size_t len, unsigned char* md5) {
	MD5_CTX ctx = { 0 };
	MD5_Init(&ctx);
	MD5_Update(&ctx, data, len);
	MD5_Final(md5, &ctx);

	return 0;
}

VOID GetFileMD5(const char* path, char* buf) {
	MD5_CTX ctx;
	int len = 0;
	unsigned  char buffer[1024] = { 0 };
	unsigned  char digest[16] = { 0 };
	FILE* pFile = fopen(path, "rb");
	if (pFile == nullptr) {
		buf = "文件访问受限";
		return;
	}
	MD5_Init(&ctx);
	while ((len = fread(buffer, 1, 1024, pFile)) > 0) {
		MD5_Update(&ctx, buffer, len);
	}
	MD5_Final(digest, &ctx);
	fclose(pFile);

	int i = 0;
	char tmp[3] = { 0 };
	for (i = 0; i < 16; i++) {
		sprintf_s(tmp, "%02X", digest[i]);
		strcat(buf, tmp);
	}
	return VOID();
}

void CMyDialogSearchKill::OnBnClickedButtonSkChoicefile() {
	// TODO: 在此添加控件通知处理程序代码
	CMyDialogChoiceFile choiceFileDialog;
	choiceFileDialog.m_SourseFlag = 2;
	choiceFileDialog.m_CmyDialogSearchKill = this;
	choiceFileDialog.DoModal();
}
BOOL checkFileMD5(CString value) {
	HANDLE hFile = CreateFile(
		md5FilePath,
		GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	char pBuffer[0x21] = { 0 };
	DWORD size = 0;
	BOOL flag = FALSE;;

	while (ReadFile(hFile, pBuffer, 0x20, &size, NULL) && size != 0) {
		pBuffer[0x20] = '\0';
		string sValue = pBuffer;
		CString MD5Value(sValue.c_str());
		if (!MD5Value.CompareNoCase(value)) {
			flag = TRUE;
			break;
		}
	}
	CloseHandle(hFile);
	return flag;
}
VOID ScanfFile(CString path, DWORD& count, CMyDialogSearchKill* dialog) {
	CString tempPath = _T("");
	CString perfectTempPath = _T("");
	tempPath = path;
	tempPath += "\\*";
	WIN32_FIND_DATA wfd = {};
	HANDLE hFile = FindFirstFile(tempPath, &wfd);
	do {
		if (StrCmp(wfd.cFileName, L".") == 0 || StrCmp(wfd.cFileName, L"..") == 0) {
			continue;
		}
		perfectTempPath = path;
		perfectTempPath += "\\";
		perfectTempPath += wfd.cFileName;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			ScanfFile(perfectTempPath, count, dialog);
		}
		else {
			int value = perfectTempPath.ReverseFind('.');
			if (value != -1) {
				char buf[33] = { 0 };
				string sPer = CT2A(perfectTempPath.GetBuffer());
				GetFileMD5(sPer.c_str(), buf);
				dialog->m_ListSanf.InsertItem(count, perfectTempPath, 0);
				string sValue = buf;
				CString MD5Value(sValue.c_str());
				dialog->m_ListSanf.SetItemText(count, 1, MD5Value);
				dialog->m_ListSanf.SetItemText(count, 2, checkFileMD5(MD5Value) ? _T("病毒") : _T("正常"));
			}
		}
	} while (FindNextFile(hFile, &wfd));
	dialog->m_ButtonDeLocal.EnableWindow(TRUE);
}
DWORD WINAPI ScanfFileProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	dialog->m_ListSanf.DeleteAllItems();
	DWORD count = 0;
	ScanfFile(dialog->m_FilePath, count, dialog);
	return true;
}

void CMyDialogSearchKill::OnBnClickedButtonLocalsk() {
	// TODO: 在此添加控件通知处理程序代码
	CreateThread(NULL, NULL, ScanfFileProc, (LPVOID)this, NULL, NULL);
}
DWORD WINAPI KillBlackProcessProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	dialog->m_ListSanf.DeleteAllItems();
	vector<string>blackProcessArray;

	ifstream fin;

	fin.open(blackProcess.c_str());
	string str;
	while (!fin.eof()) {
		getline(fin, str);
		blackProcessArray.push_back(str);
	}
	fin.close();

	HANDLE hSnapshot;
	PROCESSENTRY32 pe32;
	int n;
	int nLast;
	TCHAR buf[10];
	BOOL bSucess;
	int i = 0;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	pe32 = { sizeof(PROCESSENTRY32) };
	bSucess = Process32First(hSnapshot, &pe32);
	int count = 0;
	if (bSucess == true) {
		do {
			pe32.szExeFile;
			pe32.th32ProcessID;
			CString cs_szExeFile = pe32.szExeFile;
			string s_szExeFile = CT2A(cs_szExeFile.GetString());
			for (int j = 0; j < blackProcessArray.size(); j++) {
				if (strcmp(blackProcessArray[j].c_str(), s_szExeFile.c_str()) == 0) {
					dialog->blackProcessPID.push_back(pe32.th32ProcessID);
					dialog->m_ListSanf.InsertItem(count, cs_szExeFile, 0);
					CString pids;
					pids.Format(_T("%d"), pe32.th32ProcessID);
					dialog->m_ListSanf.SetItemText(count, 1, pids);
					count++;
				}
			}
			i++;

		} while (Process32Next(hSnapshot, &pe32));
	}

	CloseHandle(hSnapshot);
	dialog->m_ButtonCloseP.EnableWindow(TRUE);
	return 0;
}

void CMyDialogSearchKill::OnBnClickedButtonBlacksk() {
	// TODO: 在此添加控件通知处理程序代码
	CreateThread(NULL, NULL, KillBlackProcessProc, (LPVOID)this, NULL, NULL);
}


void CMyDialogSearchKill::OnBnClickedButtonSkClosep() {
	int count = 0;
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < blackProcessPID.size(); i++) {
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, blackProcessPID[i]);
		int result;
		if (processHandle != NULL) {
			result = ::TerminateProcess(processHandle, 0);
		}
		if (result != 0) {
			count++;
		}
	}
	CString message;
	message.Format(_T("成功结束了:%d个进程"), count);
	MessageBox(message);
	m_ListSanf.DeleteAllItems();
	m_ButtonCloseP.EnableWindow(FALSE);
}


void CMyDialogSearchKill::OnBnClickedButtonSkKilllocal() {
	// TODO: 在此添加控件通知处理程序代码
	m_ListSanf.DeleteAllItems();
	MessageBox(_T("杀毒成功"));
}


void CMyDialogSearchKill::OnEnChangeMfceditbrowse1() {
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_ButtonUp.EnableWindow(TRUE);
}


DWORD InitSocket() {

	WSADATA data = {};
	if (WSAStartup(MAKEWORD(2, 2), &data)) {
		return 0;
	}
	sock = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);
	if (sock == INVALID_SOCKET) {
		return 0;
	}
	SOCKADDR_IN server_addr = {};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1234);
	server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.2.147");
	connect(
		sock,
		(SOCKADDR*)&server_addr,
		sizeof(server_addr)
	);
}
void SendServiceMsg(PRequestHeader pRequestHeader) {
	send(sock, (char*)pRequestHeader, sizeof(RequestHeader), 0);
}
void GetServiceMsg(PResponseHeader pResponse) {
	recv(sock, (char*)pResponse, sizeof(ResponseHeader), 0);
}
DWORD WINAPI UploadProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	InitSocket();
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	dialog->m_EditBrowseCtrl.GetWindowTextW(path);
	char buf[33] = { 0 };
	string sPer = CT2A(path.GetBuffer());
	GetFileMD5(sPer.c_str(), buf);
	RequestHeader requestHeader = {};
	strcpy_s(requestHeader.szMd5, buf);
	requestHeader.api = RequestApi::UploadSample;
	SendServiceMsg(&requestHeader);
	ResponseHeader response = {};
	GetServiceMsg(&response);
	switch (response.code) {
	case ResultCode::SUCCESS_CODE:
		dialog->MessageBox(_T("上传成功!"));
		break;
	case ResultCode::ERROR_CODE:
		dialog->MessageBox(_T("上传失败!"));
		break;
	}
	return TRUE;
}
void CMyDialogSearchKill::OnBnClickedButtonSkUp() {
	CreateThread(NULL, NULL, UploadProc, (LPVOID)this, NULL, NULL);
}
VOID CloudSKScanfFile(DWORD threadIndex, CString path, CMyDialogSearchKill* dialog) {
	CString tempPath = _T("");
	CString perfectTempPath = _T("");
	tempPath = path;
	tempPath += "\\*";
	WIN32_FIND_DATA wfd = {};
	HANDLE hFile = FindFirstFile(tempPath, &wfd);
	do {
		if (StrCmp(wfd.cFileName, L".") == 0 || StrCmp(wfd.cFileName, L"..") == 0) {
			continue;
		}
		perfectTempPath = path;
		perfectTempPath += "\\";
		perfectTempPath += wfd.cFileName;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			CloudSKScanfFile(threadIndex, perfectTempPath, dialog);
			continue;
		}
		else {
			
			int value = perfectTempPath.ReverseFind('.');
			
			if (value != -1) {
				EnterCriticalSection(&g_cs);
				char buf[33] = { 0 };
				string sPer = CT2A(perfectTempPath.GetBuffer());
				GetFileMD5(sPer.c_str(), buf);
				dialog->m_ListSanf.InsertItem(cloudKillCount, perfectTempPath, 0);
				string sValue = buf;
				CString MD5Value(sValue.c_str());
				dialog->m_ListSanf.SetItemText(cloudKillCount, 1, MD5Value);
				dialog->m_pathArray.push_back(MD5Value);
				cloudKillCount++;
				LONG dwCount = 0;
				ReleaseSemaphore(hSemaphore, 1, &dwCount);
				LeaveCriticalSection(&g_cs);
			}
		}
	} while (FindNextFile(hFile, &wfd));
	dialog->m_ButtonDeLocal.EnableWindow(TRUE);
}
DWORD WINAPI CloudkillingProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	DWORD threadIndex = dialog->m_threadFlag;
	dialog->m_threadFlag += 1;
	CloudSKScanfFile(threadIndex, dialog->m_pszDriverArray[threadIndex], dialog);
	return TRUE;
}
DWORD WINAPI CheckMD5ForServiceProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	while (true) {
		WaitForSingleObject(hSemaphore, -1);
		InitSocket();
		CString path = dialog->m_pathArray[filePathIndex];
		char buf[33] = { 0 };
		string sPer = CT2A(path.GetBuffer());
		RequestHeader requestHeader = {};
		strcpy_s(requestHeader.szMd5, sPer.c_str());
		requestHeader.api = RequestApi::CheckMD5;
		SendServiceMsg(&requestHeader);
		ResponseHeader response = {};
		GetServiceMsg(&response);
		switch (response.code) {
		case ResultCode::SUCCESS_CODE:
			dialog->m_ListSanf.SetItemText(filePathIndex, 2, _T("正常"));
			break;
		case ResultCode::MD5_MATCHING:
			dialog->m_ListSanf.SetItemText(filePathIndex, 2, _T("病毒"));
			break;
		}

		filePathIndex++;
		if (filePathIndex > dialog->m_pathArray.size()) {
			break;
		}
	}
	return  TRUE;
}
DWORD WINAPI DeployCloudkillinProc(LPVOID lpThreadParameter) {
	CMyDialogSearchKill* dialog = (CMyDialogSearchKill*)lpThreadParameter;
	dialog->m_ListSanf.DeleteAllItems();
	DWORD dwLen = GetLogicalDriveStrings(0, NULL);
	WCHAR* pszDriver = new WCHAR[dwLen];
	GetLogicalDriveStrings(dwLen, pszDriver);
	while (*pszDriver != '\0') {
		WCHAR pszDriverShort[3] = { 0 };
		memcpy(pszDriverShort, pszDriver, 4);
		dialog->m_pszDriverArray.push_back(pszDriverShort);
		pszDriver += wcslen(pszDriver) + 1;
	}
	hSemaphore = CreateSemaphore(NULL, 0, 1000, NULL);
	//dialog->m_pszDriverArray.push_back(_T("C:\\Program Files (x86)"));
	//dialog->m_pszDriverArray.push_back(_T("D:\\app"));
	for (int i = 0; i < dialog->m_pszDriverArray.size(); i++) {
		HANDLE scanfThread = CreateThread(NULL, NULL, CloudkillingProc, lpThreadParameter, CREATE_SUSPENDED, NULL);
		dialog->fileThreadArray.push_back(scanfThread);
	}
	dialog->m_threadFlag = 0;
	DWORD old_threadFlag = 0;
	InitializeCriticalSection(&g_cs);
	while (true) {
		if ((int)dialog->m_threadFlag >= dialog->fileThreadArray.size()) {
			break;
		}
		if (dialog->m_threadFlag == old_threadFlag) {
			ResumeThread(dialog->fileThreadArray[dialog->m_threadFlag]);
			old_threadFlag++;
		}
	}
	dialog->checkThread = CreateThread(NULL, NULL, CheckMD5ForServiceProc, lpThreadParameter, NULL, NULL);
	return TRUE;
}

void CMyDialogSearchKill::OnBnClickedButtonRmsk() {
	// TODO: 在此添加控件通知处理程序代码
	fileThreadArray.clear();
	checkThread = NULL;
	m_threadFlag = 0;
	m_ListSanf.DeleteAllItems();
	CreateThread(NULL, NULL, DeployCloudkillinProc, (LPVOID)this, NULL, NULL);
	m_ButtonPause.EnableWindow(TRUE);
}


void CMyDialogSearchKill::OnBnClickedButtonRmsk2() {
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < fileThreadArray.size(); i++) {
		SuspendThread(fileThreadArray[i]);
	}
	SuspendThread(checkThread);
	m_ButtonContinue.EnableWindow(TRUE);
}


void CMyDialogSearchKill::OnBnClickedButtonRmsk3() {
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < fileThreadArray.size(); i++) {
		ResumeThread(fileThreadArray[i]);
	}
	ResumeThread(checkThread);
}
