
// Chap14_PWG.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Chap14_PWG.h"
#include "Chap14_PWGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap14PWGApp

BEGIN_MESSAGE_MAP(CChap14PWGApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CChap14PWGApp 생성

CChap14PWGApp::CChap14PWGApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CChap14PWGApp 개체입니다.

CChap14PWGApp theApp;


// CChap14PWGApp 초기화

BOOL CChap14PWGApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CChap14PWGDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}



void CChap14PWGApp::initServer()
{
	// TODO: 여기에 구현 코드 추가.
	m_pServer = new CServerSock;
	m_pServer->Create(7777); /// create는 통신할 소켓을 생성해주고 사용할 소켓에 아이피주소와 포트를 연결해주는 역할을 하는 함수임
	m_pServer->Listen(); /// 접속 요청이 있을때까지 대기하도록하는 함수
}


void CChap14PWGApp::Accept()
{
	// TODO: 여기에 구현 코드 추가.
	m_pClient = new CClientSock;
	m_pServer->Accept(*m_pClient);
	if (m_pServer)
		m_ClientList.AddTail(m_pClient); /// 서버일 경우 클라이언트를 리스트에 저장
	CString strSock;
	UINT nPort;
	m_pClient->GetPeerName(strSock, nPort);
	((CChap14PWGDlg*)m_pMainWnd)->Accept(strSock);
}


void CChap14PWGApp::CleanUp()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_pServer) {
		delete m_pServer;
		POSITION pos = m_ClientList.GetHeadPosition();
		m_ClientList.RemoveAt(pos);
		delete m_pClient;
	}
	if (m_pClient)
		delete m_pClient;
}


void CChap14PWGApp::Connect(CString strIP)
{
	// TODO: 여기에 구현 코드 추가.
	m_pClient = new CClientSock;
	m_pClient->Create();
	m_pClient->Connect(strIP, 7777);
}


void CChap14PWGApp::ReceiveData(CClientSock* pSock)
{
	// TODO: 여기에 구현 코드 추가.
	wchar_t temp[MAX_PATH];
	pSock->Receive(temp, sizeof(temp));
	if (m_pServer) {

		POSITION pos = m_ClientList.GetHeadPosition();
		((CChap14PWGDlg*)m_pMainWnd)->ReceiveData(temp);
		while (pos != NULL) {
			m_pClient = (CClientSock*)m_ClientList.GetAt(pos);
			m_ClientList.GetNext(pos);

			if (m_pClient != pSock)
				m_pClient->Send(temp, sizeof(temp));
		}
	}
	else if (m_pClient)
		((CChap14PWGDlg*)m_pMainWnd)->ReceiveData(temp);
}


void CChap14PWGApp::SendData(CString strData) /// 패킷 주고받으려는 
{
	// TODO: 여기에 구현 코드 추가.
	if (m_pServer) {
		POSITION pos = m_ClientList.GetHeadPosition();
		while (pos != NULL) {
			m_pClient = (CClientSock*)m_ClientList.GetAt(pos);
			m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
			m_ClientList.GetNext(pos);
		}
	}
	else if (m_pClient) {
		m_pClient->Send((LPCTSTR)strData, sizeof(TCHAR)*(strData.GetLength() + 1));
	}
}


void CChap14PWGApp::CloseChild(CClientSock* pClose)
{
	// TODO: 여기에 구현 코드 추가.
	CString ExitIP;

	if (m_pServer) {
		POSITION pos = m_ClientList.Find(pClose);

		if (pos != NULL) {
			m_pClient = (CClientSock*)m_ClientList.GetAt(pos);
			ExitIP = m_pClient->m_strMyIP;
			m_ClientList.RemoveAt(pos);
			delete m_pClient;
			m_pClient = NULL;
		}
	}
	else if (m_pClient) {
		delete m_pClient;
		m_pClient = NULL;
		AfxMessageBox(_T("서버와의 연결이 해지되었습니다."));
	}

	CString str;
	str.Format(_T("[%s]님이 퇴장하셨습니다."),  ExitIP);
	AfxMessageBox(str);
}
