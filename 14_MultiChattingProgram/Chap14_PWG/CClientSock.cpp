// CClientSock.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap14_PWG.h"
#include "CClientSock.h"
#include "Chap14_PWGDlg.h"


// CClientSock

CClientSock::CClientSock()
{
	char name[50];
	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {
		if ((hostinfo = gethostbyname(name)) != NULL) {
			m_strMyIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
		}
	}
}

CClientSock::~CClientSock()
{
}


// CClientSock 멤버 함수


void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	((CChap14PWGApp*)AfxGetApp())->ReceiveData(/*((CChap14PWGApp*)AfxGetApp())->m_pClient*/this);

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//POSITION pos = ((CChap14PWGApp*)AfxGetApp())->m_ClientList->GetHeadPosition();

	((CChap14PWGApp*)AfxGetApp())->CloseChild(/*((CChap14PWGApp*)AfxGetApp())->m_pClient*/this);

	CAsyncSocket::OnClose(nErrorCode);
}
