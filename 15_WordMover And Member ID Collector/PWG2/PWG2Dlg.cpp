
// PWG2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "PWG2.h"
#include "PWG2Dlg.h"
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


// CPWG2Dlg 대화 상자



CPWG2Dlg::CPWG2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PWG2_DIALOG, pParent)
	, m_strName(_T(""))
	, m_nGender(0)
	, m_bSubject1(FALSE)
	, m_bSubject2(FALSE)
	, m_bSubject3(FALSE)
	, m_bSubject4(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPWG2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Radio(pDX, IDC_RADIO_MAN, m_nGender);
	DDX_Control(pDX, IDC_COMBO_AGE, m_cbAge);
	DDX_Check(pDX, IDC_CHECK1, m_bSubject1);
	DDX_Check(pDX, IDC_CHECK2, m_bSubject2);
	DDX_Check(pDX, IDC_CHECK3, m_bSubject3);
	DDX_Check(pDX, IDC_CHECK4, m_bSubject4);
	DDX_Control(pDX, IDC_LIST_INFO, m_listInfo);
}

BEGIN_MESSAGE_MAP(CPWG2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CPWG2Dlg::OnBnClickedButtonJoin)
	ON_LBN_SELCHANGE(IDC_LIST_INFO, &CPWG2Dlg::OnLbnSelchangeListInfo)
	ON_BN_CLICKED(IDC_BUTTON_WITHDRAWAL, &CPWG2Dlg::OnBnClickedButtonWithdrawal)
END_MESSAGE_MAP()


// CPWG2Dlg 메시지 처리기

BOOL CPWG2Dlg::OnInitDialog()
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
	for (int i = 1960; i <= 2018; i++) {
		CString str;
		str.Format(_T("%d"), i);
		m_cbAge.AddString(str);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPWG2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPWG2Dlg::OnPaint()
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
HCURSOR CPWG2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPWG2Dlg::OnBnClickedButtonJoin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	if (m_strName != _T("") &&
		m_cbAge.GetCurSel() != CB_ERR &&
		(m_bSubject1 == 0 && m_bSubject2 == 0 && m_bSubject3 == 0 && m_bSubject4 == 0) != true)
	{
		CString strGender;
		switch (m_nGender) {
		case 0:
			strGender = _T("남성");
			break;
		case 1:
			strGender.Format(_T("여성"));
			break;
		}

		int index = m_cbAge.GetCurSel();
		CString strAge;
		m_cbAge.GetLBText(index, strAge);
		int nAge = 2019 - (_ttoi(strAge));

		CString strSubject;
		if (m_bSubject1 == 1)
			strSubject += _T("앱 개발,");
		if (m_bSubject2 == 1)
			strSubject += _T("영상처리,");
		if (m_bSubject3 == 1)
			strSubject += _T("네트워크 보안,");
		if (m_bSubject4 == 1)
			strSubject += _T("게임프로그래밍,");

		CString strInfo;
		strInfo.Format(_T("%s:%s:%d:%s"), m_strName, strGender, nAge, strSubject);
		strInfo.TrimRight(_T(","));

		m_listInfo.AddString(strInfo);

		m_strName.Empty();
		m_nGender = 0;
		m_bSubject1 = 0;
		m_bSubject2 = 0;
		m_bSubject3 = 0;
		m_bSubject4 = 0;
		m_cbAge.SetCurSel(-1);

		UpdateData(false);
	}
	else {
		AfxMessageBox(_T("공백란을 모두 채워주세요."));
	}
}


void CPWG2Dlg::OnLbnSelchangeListInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_listInfo.GetCurSel();

	if (index == LB_ERR) {
		AfxMessageBox(_T("공백란이 아닌 문자열을 선택해주세요."));
	}
	else {
		m_bSubject1 = false;
		m_bSubject2 = false;
		m_bSubject3 = false;
		m_bSubject4 = false;

		CString strList;
		m_listInfo.GetText(index, strList);

		CString temp[7];
		CString resToken;
		int curPos = 0;
		int i = 0;

		resToken = strList.Tokenize(_T(":,"), curPos);
		while (resToken != _T(""))
		{
			temp[i].Format(resToken);
			resToken = strList.Tokenize(_T(":,"), curPos);
			i++;
		};

		m_strName = temp[0];

		if (temp[1] == _T("남성"))
			m_nGender = 0;
		else if(temp[1] == _T("여성"))
			m_nGender = 1;

		int nAge = _ttoi(temp[2]);
		
		int cbIndex = 59 - nAge;
		m_cbAge.SetCurSel(cbIndex);

		for (int i = 3; i < 7; i++) {
			if (temp[i] == _T("앱 개발"))
				m_bSubject1 = true;
			if (temp[i] == _T("영상처리"))
				m_bSubject2 = true;
			if (temp[i] == _T("네트워크 보안"))
				m_bSubject3 = true;
			if (temp[i] == _T("게임프로그래밍"))
				m_bSubject4 = true;
		}

		UpdateData(false);
	}
}


void CPWG2Dlg::OnBnClickedButtonWithdrawal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_listInfo.GetCurSel();
	m_listInfo.DeleteString(index);
}
