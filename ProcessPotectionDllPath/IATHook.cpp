#include "pch.h"
#include "IATHOOK.h"
#include <Windows.h>
#include <tchar.h>

DWORD oldFuncAdress = 0;
WCHAR pid[0x20] = { 0 };
HANDLE WINAPI MyOpenProcess(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_In_ DWORD dwProcessId
) {
	DWORD dPid = 0;
	_stscanf_s(pid, _T("%d"), &dPid);
	if (dPid == dwProcessId) {
		MessageBox(NULL, _T("这个进程是受保护的"), NULL, NULL);
		return NULL;
	}
	return OpenProcess(dwDesiredAccess,bInheritHandle,dwProcessId);
}
DWORD WINAPI GetProcessPotectionPIDProc(LPVOID lpThreadParameter) {
	PVOID pBuf;
	HANDLE hMapFile;
	while (true) {
		hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 16, L"ProcessManagerPID");
		if (hMapFile == NULL) {
			continue;
		}
		pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 16);
		if (pBuf == NULL) {
			continue;
		}
		wcscpy_s(pid, (LPWSTR)pBuf);
		if (wcscmp(L"", pid) == 0) {
			continue;
		}
		*((WCHAR*)pBuf) = 0;
		break;
	}
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	return true;
}
void SetIATHook() {
	
	//找到旧函数的地址
	oldFuncAdress = (DWORD)GetProcAddress(LoadLibrary(_T("kernel32.dll")), "OpenProcess");
	//获得主模块基址
	HMODULE imageBase = GetModuleHandle(NULL);
	char* pBuf = (char*)imageBase;
	PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)pBuf;
	PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pBuf + pDos->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDataDir = pNt->OptionalHeader.DataDirectory;
	PIMAGE_IMPORT_DESCRIPTOR pImport =
		(PIMAGE_IMPORT_DESCRIPTOR)(pDataDir[1].VirtualAddress + pBuf);
	while (pImport->FirstThunk != 0) {
		DWORD* funAddr = (DWORD*)(pBuf + pImport->FirstThunk);
		while (*funAddr != 0) {
			if (*funAddr == oldFuncAdress) {
				DWORD value = 0;
				VirtualProtect(funAddr, 1, PAGE_EXECUTE_READWRITE, &value);
				*funAddr = (DWORD)MyOpenProcess;
				CreateThread(NULL, NULL, GetProcessPotectionPIDProc, NULL, NULL, NULL);
				return;
			}
			funAddr++;
		}
		pImport++;
	}

}