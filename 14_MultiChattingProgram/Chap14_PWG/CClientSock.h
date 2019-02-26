#pragma once
#include <afxsock.h>

// CClientSock 명령 대상

class CClientSock : public CAsyncSocket
{
public:
	CClientSock();
	virtual ~CClientSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
//	CString m_strClientIP;
	CString m_strMyIP;
};


