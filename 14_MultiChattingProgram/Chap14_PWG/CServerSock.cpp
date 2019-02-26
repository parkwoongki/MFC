#include "stdafx.h"
#include "CServerSock.h"
#include "Chap14_PWG.h"

CServerSock::CServerSock()
{

}


CServerSock::~CServerSock()
{
}


void CServerSock::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CChap14PWGApp*)AfxGetApp())->Accept();

	CAsyncSocket::OnAccept(nErrorCode);
}
