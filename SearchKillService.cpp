// SearchKillService.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include "MyStruct.h"
#include <stdio.h>
#include <WinSock2.h>
#include "Service.h"
#pragma comment(lib,"ws2_32.lib")
SOCKET sock_server = NULL;

DWORD WINAPI SendMsg(LPVOID lpThreadParameter) {
	PResponseHeader pRes = (PResponseHeader)lpThreadParameter;
	send(pRes->sock_client, (char*)pRes, sizeof(ResponseHeader), 0);
	return TRUE;
}

DWORD WINAPI ApiHandleProc(LPVOID lpThreadParameter) {
	PRequestHeader pRequestHeader = (PRequestHeader)lpThreadParameter;
	ResponseHeader res;
	switch (pRequestHeader->api) {
	case RequestApi::UploadSample: {
		res = SaveMD5Value(pRequestHeader);
		res.sock_client = pRequestHeader->sock_client;
		HANDLE thread = CreateThread(NULL, NULL, SendMsg, (LPVOID)&res, NULL, NULL);
		WaitForSingleObject(thread, -1);
	}
								 break;
	case RequestApi::CheckMD5: {
		res = CheckMD5Value(pRequestHeader);
		res.sock_client = pRequestHeader->sock_client;
		HANDLE thread = CreateThread(NULL, NULL, SendMsg, (LPVOID)&res, NULL, NULL);
		WaitForSingleObject(thread, -1);
	}
							 break;
	}
	return true;
}
int StartService() {
	WSADATA data = {};
	if (WSAStartup(MAKEWORD(2, 2), &data)) {
		printf("初始化环境出错\n");
		return 0;
	}
	// 2. 创建套接字
	sock_server = socket(
		AF_INET,		// 通信协议类型
		SOCK_STREAM,	// 套接字类型
		IPPROTO_TCP		// 具体协议
	);
	if (sock_server == INVALID_SOCKET) {
		printf("创建套接字失败\n");
		return 0;
	}

	// 3. 绑定套接字
	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;		//网络协议
	// 需要将主机字节序转换成网络字节序
	// 0x12345678    [78 56 34 21] 小端
	// 0x12345678    [12 34 56 78] 大端
	addr.sin_port = htons(1234);	// 设置端口
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.2.147");

	int bret = bind(
		sock_server,				//套接字
		(SOCKADDR*)&addr,			//服务器的地址信息
		sizeof(addr)				//地址大小
	);
	if (bret == SOCKET_ERROR) {
		printf("绑定失败\n");
		return 0;
	}
	// 4.监听套接字
	bret = listen(
		sock_server,		//服务套接字
		SOMAXCONN);			// 监听最大数，一次可以处理的客户端
	printf("服务正在监听.......\n");
	SOCKADDR_IN client_add = {};
	int  add_len = sizeof(client_add);
	while (true) {
		SOCKET sock_client = accept(
			sock_server,				// 服务套接字
			(SOCKADDR*)&client_add,		// 客户端的地址信息
			&add_len					// 地址信息长度，必须填充真实长度
		);
		char buff[1024] = { 0 };
		recv(
			sock_client,		//客户端套接字
			buff,				//接受数据的缓冲区
			1024,				//缓冲区大小
			0					//标志
		);
		if (sock_client != NULL) {
			RequestHeader req;
			memcpy(&req, buff, sizeof(RequestHeader));
			req.sock_client = NULL;
			req.sock_client = sock_client;
			CreateThread(NULL, NULL, ApiHandleProc, (LPVOID)&req, NULL, NULL);
		}
	}

}

int main() {
	InitMySql();
	StartService();
	// 5.关闭套接字
	closesocket(sock_server);

	// 6.清理环境
	WSACleanup();
}

