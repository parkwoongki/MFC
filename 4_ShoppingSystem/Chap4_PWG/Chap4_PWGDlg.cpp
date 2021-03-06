
// Chap4_PWGDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap4_PWG.h"
#include "Chap4_PWGDlg.h"
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


// CChap4PWGDlg 대화 상자



CChap4PWGDlg::CChap4PWGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAP4_PWG_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChap4PWGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LEFT, m_listLeft);
	DDX_Control(pDX, IDC_LIST_RIGHT, m_listRight);
	DDX_Control(pDX, IDC_COMBO_MOVE, m_cbMove);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CChap4PWGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST_LEFT, &CChap4PWGDlg::OnLbnSelchangeListLeft)
	ON_LBN_SELCHANGE(IDC_LIST_RIGHT, &CChap4PWGDlg::OnLbnSelchangeListRight)
	ON_CBN_SELCHANGE(IDC_COMBO_MOVE, &CChap4PWGDlg::OnCbnSelchangeComboMove)
	ON_EN_CHANGE(IDC_EDIT_RESULT, &CChap4PWGDlg::OnEnChangeEditResult)
	ON_BN_CLICKED(IDC_BUTTON_PURCHASE, &CChap4PWGDlg::OnBnClickedButtonPurchase)
END_MESSAGE_MAP()


// CChap4PWGDlg 메시지 처리기

BOOL CChap4PWGDlg::OnInitDialog()
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

	m_listLeft.AddString(_T("복숭아"));
	m_listLeft.AddString(_T("딸기"));
	m_listLeft.AddString(_T("사과"));
	m_listLeft.AddString(_T("바나나"));
	m_listLeft.AddString(_T("수박"));
	m_listLeft.AddString(_T("삼겹살"));
	m_listLeft.AddString(_T("참기름"));
	m_listLeft.AddString(_T("양파"));
	m_listLeft.AddString(_T("계란"));
	m_listLeft.AddString(_T("감자"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChap4PWGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChap4PWGDlg::OnPaint()
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
HCURSOR CChap4PWGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChap4PWGDlg::OnLbnSelchangeListLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChap4PWGDlg::OnLbnSelchangeListRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChap4PWGDlg::OnCbnSelchangeComboMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString selected_item; /// 선택된 아이템

	int left_index = m_listLeft.GetCurSel(); /// 왼쪽 리스트에서 고른 물건의 위치
	int right_index = m_listRight.GetCurSel(); /// 오른쪽 리스트에서 고른 물건의 위치
	int choose_index = m_cbMove.GetCurSel(); /// -> 인지, <- 인지

	if (choose_index == 0 && left_index != LB_ERR) {
		m_listLeft.GetText(left_index, selected_item); /// 아이템을 고르고,

		/* 옮겨주고, */
		m_listRight.AddString(selected_item);
		m_listLeft.DeleteString(left_index);

		m_listLeft.SetCurSel(left_index); /// 자동으로 다음 아이템을 고름
	}
	else if (choose_index == 1 && right_index != LB_ERR) {
		m_listRight.GetText(right_index, selected_item); /// 선택 했던 아이템을 다시 고르고,
		
		/* 다시 왼쪽 리스트에 되돌려놓고 */
		m_listLeft.AddString(selected_item);
		m_listRight.DeleteString(right_index);

		m_listRight.SetCurSel(right_index); /// 자동으로 다음 아이템을 고름
	}
	else if (choose_index == 0 && left_index == LB_ERR) { /// 왼쪽 리스트에서 선택을 안했는데 콤보 박스에서 오른쪽으로 물건 옮기는 화살표 선택했을 때
		AfxMessageBox(_T("왼쪽 리스트 박스에서 이동할 아이템을 선택해주세요."));
	}
	else if (choose_index == 1 && right_index == LB_ERR) { /// 오른쪽 리스트에서 선택을 안했는데 콤보 박스에서 왼쪽으로 물건 옮기는 화살표 선택했을 때
		AfxMessageBox(_T("오른쪽 리스트 박스에서 이동할 아이템을 선택해주세요."));
	}
}


void CChap4PWGDlg::OnEnChangeEditResult()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChap4PWGDlg::OnBnClickedButtonPurchase()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString purchased_item;
	CString sum_item;

	int index = m_listRight.GetCount();

	for (int i = 0; i < index; i++) {
		m_listRight.GetText(i, purchased_item); /// 구매 물품 스트링 변수에 리스트에 있는 아이템 읽어온 후,
		sum_item = sum_item + purchased_item + _T("\r\n"); /// 모든 물품을 종합하는 스트링 변수에 다 합해줌
	}

	m_strResult.Format(sum_item);
	UpdateData(false);
}
