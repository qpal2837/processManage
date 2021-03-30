#pragma once
#include <WinSock2.h>
enum RequestApi {
	UploadSample = 100,
	CheckMD5 = 200,
};

enum ResultCode {
	SUCCESS_CODE = 200,
	MD5_MATCHING = 201,
	ERROR_CODE = 500,
};
typedef struct _RequestHeader {
	RequestApi api;
	int ulFileSize;
	char szMd5[33];
	SOCKET sock_client;

}RequestHeader, * PRequestHeader;

typedef struct _ResponseHeader {
	ResultCode code;
	SOCKET sock_client;
}ResponseHeader,*PResponseHeader;

