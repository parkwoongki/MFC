
// Chap11_PWGDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap11_PWG.h"
#include "Chap11_PWGDlg.h"
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


// CChap11PWGDlg 대화 상자



CChap11PWGDlg::CChap11PWGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAP11_PWG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChap11PWGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChap11PWGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_A, &CChap11PWGDlg::OnBnClickedRadioA)
	ON_BN_CLICKED(IDC_RADIO_B, &CChap11PWGDlg::OnBnClickedRadioB)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CChap11PWGDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CChap11PWGDlg::OnBnClickedButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CChap11PWGDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CChap11PWGDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_BACK_SPACE, &CChap11PWGDlg::OnBnClickedButtonBackSpace)
	ON_BN_CLICKED(IDC_BUTTON_1, &CChap11PWGDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CChap11PWGDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CChap11PWGDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CChap11PWGDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CChap11PWGDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CChap11PWGDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CChap11PWGDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CChap11PWGDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CChap11PWGDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CChap11PWGDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CChap11PWGDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CChap11PWGDlg 메시지 처리기

BOOL CChap11PWGDlg::OnInitDialog()
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
	m_bRadio[0] = m_bRadio[1] = false;
	/*SetDlgItemText(IDC_EDIT_RESULT, _T("0"));
	SetDlgItemText(IDC_EDIT_A, _T("0"));
	SetDlgItemText(IDC_EDIT_B, _T("0"));*/

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChap11PWGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChap11PWGDlg::OnPaint()
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
HCURSOR CChap11PWGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChap11PWGDlg::OnBnClickedRadioA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bRadio[0] = !m_bRadio[0];

	if (m_bRadio[1])
		m_bRadio[1] = !m_bRadio[1];
}


void CChap11PWGDlg::OnBnClickedRadioB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bRadio[1] = !m_bRadio[1];

	if (m_bRadio[0])
		m_bRadio[0] = !m_bRadio[0];
}


void CChap11PWGDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strResult, strA, strB;
	double fA, fB;

	GetDlgItemText(IDC_EDIT_A, strA);
	fA = _wtof(strA);
	GetDlgItemText(IDC_EDIT_B, strB);
	fB = _wtof(strB);

	strResult.Format(_T("%g"), m_calcCalculater.Add(fA, fB));

	if (strA == _T("") || strB == _T("")) {
		AfxMessageBox(_T("숫자를 모두 입력하시오."));
		SetDlgItemText(IDC_EDIT_RESULT, _T(""));
	}
	else
		SetDlgItemText(IDC_EDIT_RESULT, strResult);
}


void CChap11PWGDlg::OnBnClickedButtonSub()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strResult, strA, strB;
	double fA, fB;

	GetDlgItemText(IDC_EDIT_A, strA);
	fA = _wtof(strA);
	GetDlgItemText(IDC_EDIT_B, strB);
	fB = _wtof(strB);

	strResult.Format(_T("%g"), m_calcCalculater.Sub(fA, fB));

	if (strA == _T("") || strB == _T("")) {
		AfxMessageBox(_T("숫자를 모두 입력하시오."));
		SetDlgItemText(IDC_EDIT_RESULT, _T(""));
	}
	else
		SetDlgItemText(IDC_EDIT_RESULT, strResult);
}


void CChap11PWGDlg::OnBnClickedButtonMul()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strResult, strA, strB;
	double fA, fB;

	GetDlgItemText(IDC_EDIT_A, strA);
	fA = _wtof(strA);
	GetDlgItemText(IDC_EDIT_B, strB);
	fB = _wtof(strB);

	strResult.Format(_T("%g"), m_calcCalculater.Mul(fA, fB));

	if (strA == _T("") || strB == _T("")) {
		AfxMessageBox(_T("숫자를 모두 입력하시오."));
		SetDlgItemText(IDC_EDIT_RESULT, _T(""));
	}
	else
		SetDlgItemText(IDC_EDIT_RESULT, strResult);
}


void CChap11PWGDlg::OnBnClickedButtonDiv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strResult, strA, strB;
	double fA, fB;

	GetDlgItemText(IDC_EDIT_A, strA);
	fA = _wtof(strA);
	GetDlgItemText(IDC_EDIT_B, strB);
	fB = _wtof(strB);

	if (strA == _T("") || strB == _T("")) {
		AfxMessageBox(_T("숫자를 모두 입력하시오."));
		SetDlgItemText(IDC_EDIT_RESULT, _T(""));
	}
	else {
		if (fB != 0) {
			strResult.Format(_T("%g"), m_calcCalculater.Div(fA, fB));
			SetDlgItemText(IDC_EDIT_RESULT, strResult);
		}
		else
			AfxMessageBox(_T("0으로 나눌 수 없습니다."));
	}
}


void CChap11PWGDlg::OnBnClickedButtonBackSpace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;
	int length;

	if (m_bRadio[0]) {
		GetDlgItemText(IDC_EDIT_A, strTemp);
		length = strTemp.GetLength();
		strTemp.Delete(length-1, 1);
		strTemp.Format(_T("%g"), _wtof(strTemp));
		if(strTemp == _T("0"))
			SetDlgItemText(IDC_EDIT_A, _T(""));
		else
			SetDlgItemText(IDC_EDIT_A, strTemp);
	}
	else {
		GetDlgItemText(IDC_EDIT_B, strTemp);
		length = strTemp.GetLength();
		strTemp.Delete(length-1, 1);
		strTemp.Format(_T("%g"), _wtof(strTemp));
		if (strTemp == _T("0"))
			SetDlgItemText(IDC_EDIT_B, _T(""));
		else
			SetDlgItemText(IDC_EDIT_B, strTemp);
	}
}


void CChap11PWGDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("1"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("1"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("2"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("2"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("3"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("3"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("4"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("4"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("5"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("5"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("6"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("6"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("7"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("7"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("8"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("8"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("9"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("9"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButton0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	if (m_bRadio[0] == false && m_bRadio[1] == false) {
		AfxMessageBox(_T("먼저 입력하려는 숫자의 라디오 버튼을 선택하세요."));
	}
	else {
		if (m_bRadio[0]) {
			GetDlgItemText(IDC_EDIT_A, strTemp);
			strTemp.Append(_T("0"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_A, strTemp);
		}
		else {
			GetDlgItemText(IDC_EDIT_B, strTemp);
			strTemp.Append(_T("0"));
			strTemp.Format(_T("%g"), _wtof(strTemp));
			SetDlgItemText(IDC_EDIT_B, strTemp);
		}
	}
}


void CChap11PWGDlg::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("계산 결과를 초기화합니다!"));
	SetDlgItemText(IDC_EDIT_RESULT, _T(""));
	SetDlgItemText(IDC_EDIT_A, _T(""));
	SetDlgItemText(IDC_EDIT_B, _T(""));
	((CButton*)GetDlgItem(IDC_RADIO_A))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_B))->SetCheck(FALSE);
	m_bRadio[0] = m_bRadio[1] = false;
}
