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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CChap14PWGApp*)AfxGetApp())->Accept();

	CAsyncSocket::OnAccept(nErrorCode);
}
