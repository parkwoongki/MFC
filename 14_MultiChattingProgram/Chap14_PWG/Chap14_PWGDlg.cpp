
// Chap14_PWGDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap14_PWG.h"
#include "Chap14_PWGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChap14PWGDlg 대화 상자



CChap14PWGDlg::CChap14PWGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATTING_DIALOG, pParent)
	, m_nChatMode(0)
	, m_strMyIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChap14PWGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAddress);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Radio(pDX, IDC_RADIO_SERVER, m_nChatMode);
	//  DDX_Control(pDX, IDC_BUTTON_CONNECT, m_strMyIP);
}

BEGIN_MESSAGE_MAP(CChap14PWGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CChap14PWGDlg::OnClickedRadioServer)
	ON_COMMAND(IDC_RADIO_CLIENT, &CChap14PWGDlg::OnRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChap14PWGDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChap14PWGDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// CChap14PWGDlg 메시지 처리기

BOOL CChap14PWGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// IP 주소 가져오기!
	char name[50];
	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {
		if ((hostinfo = gethostbyname(name)) != NULL) {
			m_strMyIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
		}
	}

	// 컨트롤 초기화!
	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE); /// 마음대로 못쓰게 만드는것임.
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Open"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChap14PWGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChap14PWGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChap14PWGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChap14PWGDlg::OnClickedRadioServer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_IPAddress.SetWindowText(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Open"));
}


void CChap14PWGDlg::OnRadioClient()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_IPAddress.SetWindowText(_T(""));
	m_IPAddress.EnableWindow(TRUE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
}


void CChap14PWGDlg::OnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	if (!m_nChatMode) {
		((CChap14PWGApp*)AfxGetApp())->initServer();
		GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	}
	else {
		CString strIP;
		GetDlgItemText(IDC_IPADDRESS_SERVER,strIP);
		if (strIP != _T("0.0.0.0")) {
			GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
			((CChap14PWGApp*)AfxGetApp())->Connect(strIP);
			m_strOtherIP = strIP;
		}
		else
			AfxMessageBox(_T("접속할 서버의 IP주소를 입력하세요."));
	}
}


void CChap14PWGDlg::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSend, strInsert;
	GetDlgItemText(IDC_EDIT_SEND, strSend);
	strInsert.Format(_T("[%s]:%s"), m_strMyIP, strSend);
	theApp.SendData(strInsert);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
	SetDlgItemText(IDC_EDIT_SEND, _T(""));
}


void CChap14PWGDlg::ReceiveData(CString strReceive)
{
	// TODO: 여기에 구현 코드 추가.
	CString strInsert;
	strInsert.Format(_T("%s"),/* m_strOtherIP,*/ strReceive);
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);
}


void CChap14PWGDlg::Accept(CString strSock)
{
	// TODO: 여기에 구현 코드 추가.
	m_strOtherIP = strSock;
}
