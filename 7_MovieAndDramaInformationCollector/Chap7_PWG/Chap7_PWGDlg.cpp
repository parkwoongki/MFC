
// Chap7_PWGDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap7_PWG.h"
#include "Chap7_PWGDlg.h"
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


// CChap7PWGDlg 대화 상자



CChap7PWGDlg::CChap7PWGDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAP7_PWG_DIALOG, pParent)
	, m_strTitle(_T(""))
	, m_strWhen(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChap7PWGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_GENRE, m_treeGenre);
	DDX_Control(pDX, IDC_LIST_PIECE, m_listPiece);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_WHEN, m_strWhen);
	DDX_Control(pDX, IDC_COMBO_RATE, m_cbRate);
}

BEGIN_MESSAGE_MAP(CChap7PWGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CChap7PWGDlg::OnBnClickedButtonInsert)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_GENRE, &CChap7PWGDlg::OnTvnSelchangedTreeGenre)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PIECE, &CChap7PWGDlg::OnLvnItemchangedListPiece)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CChap7PWGDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CChap7PWGDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CChap7PWGDlg 메시지 처리기

BOOL CChap7PWGDlg::OnInitDialog()
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

	LPWSTR list[3] = { _T("제품명"), _T("제작년도"), _T("등급") };
	int nWidth[3] = { 144,120,130 };

	// List Control의 칼럼을 설정한다.
	for (int i = 0; i < 3; i++)
		m_listPiece.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);

	// List Control의 스타일 변ㄱㅇ을 위한 콤보 상자의 초기 선택값 지정
	m_listPiece.SetExtendedStyle(m_listPiece.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE))->SetCurSel(0);

	m_hRoot = m_treeGenre.InsertItem(_T("영상물"), 0, TVI_LAST);
	m_hMovie = m_treeGenre.InsertItem(_T("영화"), m_hRoot, TVI_LAST);
	m_treeGenre.Expand(m_hRoot, TVE_EXPAND);
	m_hDrama = m_treeGenre.InsertItem(_T("드라마"), m_hRoot, TVI_LAST);
	m_treeGenre.Expand(m_hRoot, TVE_EXPAND);

	// 수정/삭제 버튼을 비활성화 시킨다.
	//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	//((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChap7PWGDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChap7PWGDlg::OnPaint()
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
HCURSOR CChap7PWGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChap7PWGDlg::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_listPiece.GetItemCount();
	int index = m_cbRate.GetCurSel();
	CString strRate;

	UpdateData(TRUE);
	
	if (m_hSelectedNode == m_hMovie) {
		if (!m_strTitle.IsEmpty() && !m_strWhen.IsEmpty()) {
			bool bFine = true;

			for (int i = 0; i < m_nCount; i++) {
				if (m_productInfo[i].strTitle==m_strTitle && m_productInfo[i].strCategory==_T("Movie")) {
					bFine = false;
				}
			}
			
			if (bFine) {
				/// 리스트 컨트롤에 나타내기
				m_listPiece.InsertItem(nCount + 1, m_strTitle);
				m_listPiece.SetItem(nCount, 1, LVIF_TEXT, m_strWhen, 0, 0, 0, 0);
				m_cbRate.GetLBText(index, strRate);
				m_listPiece.SetItem(nCount, 2, LVIF_TEXT, strRate, 0, 0, 0, 0);

				/// 구조체 배열에 정보 넣기
				m_productInfo[m_nCount].strCategory = _T("Movie");
				m_productInfo[m_nCount].strTitle = m_strTitle;
				m_productInfo[m_nCount].strGrade = strRate;
				m_productInfo[m_nCount].strYear = m_strWhen;
				m_nCount++;

				/// 컨트롤에 써져있는거 지워주기
				m_strTitle.Empty();
				m_strWhen.Empty();

				// 수정/삭제 버튼을 비활성화 시킨다.
				//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
				//((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

				UpdateData(FALSE);
			}
			else 
				MessageBox(_T("중복된 작품이 있습니다."), _T("잠깐!"), MB_OK);
		}
		else 
			MessageBox(_T("모든 항목을 입력해 주세요."), _T("잠깐!"), MB_OK);
	}
	else if (m_hSelectedNode == m_hDrama) {
		if (!m_strTitle.IsEmpty() && !m_strWhen.IsEmpty()) {
			bool bFine = true;

			for (int i = 0; i < m_nCount; i++) {
				if (m_productInfo[i].strTitle == m_strTitle && m_productInfo[i].strCategory == _T("Drama")) {
					bFine = false;
				}
			}

			if (bFine) {
				/// 리스트 컨트롤에 나타내기
				m_listPiece.InsertItem(nCount + 1, m_strTitle);
				m_listPiece.SetItem(nCount, 1, LVIF_TEXT, m_strWhen, 0, 0, 0, 0);
				m_cbRate.GetLBText(index, strRate);
				m_listPiece.SetItem(nCount, 2, LVIF_TEXT, strRate, 0, 0, 0, 0);

				/// 구조체 배열에 정보 넣기
				m_productInfo[m_nCount].strCategory = _T("Drama");
				m_productInfo[m_nCount].strTitle = m_strTitle;
				m_productInfo[m_nCount].strGrade = strRate;
				m_productInfo[m_nCount].strYear = m_strWhen;
				m_nCount++;

				/// 컨트롤에 써져있는거 지워주기
				m_strTitle.Empty();
				m_strWhen.Empty();

				// 수정/삭제 버튼을 비활성화 시킨다.
				//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
				//((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

				UpdateData(FALSE);
			}
			else
				MessageBox(_T("중복된 작품이 있습니다."), _T("잠깐!"), MB_OK);
		}
		else {
			MessageBox(_T("모든 항목을 입력해 주세요."), _T("잠깐!"), MB_OK);
		}
	}
	else {
		MessageBox(_T("작품 장르를 선택해주세요."), _T("잠깐!"), MB_OK);
	}

	m_strTitle.Empty();
	m_strWhen.Empty();
	m_cbRate.SetCurSel(0);

	UpdateData(FALSE);
}


void CChap7PWGDlg::OnTvnSelchangedTreeGenre(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	m_listPiece.DeleteAllItems();
	m_nAllCount = 0;
	m_nMovieCount = 0;
	m_nDramaCount = 0;

	for (int i = 0; i < m_nCount; i++) {
		if (m_hSelectedNode == m_hRoot) {
			m_listPiece.InsertItem(i + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(i, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(i, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
		}
		else if (m_hSelectedNode == m_hMovie && m_productInfo[i].strCategory == _T("Movie")) {
			m_listPiece.InsertItem(m_nMovieCount + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(m_nMovieCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(m_nMovieCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			m_nMovieCount++;
		}
		else if (m_hSelectedNode == m_hDrama && m_productInfo[i].strCategory == _T("Drama")) {
			m_listPiece.InsertItem(m_nDramaCount + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(m_nDramaCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(m_nDramaCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			m_nDramaCount++;
		}
	}

	m_strTitle.Empty();
	m_strWhen.Empty();
	m_cbRate.SetCurSel(0);

	UpdateData(FALSE);

	*pResult = 0;
}


void CChap7PWGDlg::OnLvnItemchangedListPiece(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;
	
	m_strTitle = m_listPiece.GetItemText(m_nSelectedItem, 0);
	m_strWhen = m_listPiece.GetItemText(m_nSelectedItem, 1);
	if (m_listPiece.GetItemText(m_nSelectedItem, 2) == _T("12세 이상 관람"))
		m_cbRate.SetCurSel(0);
	else if (m_listPiece.GetItemText(m_nSelectedItem, 2) == _T("15세 이상 관람"))
		m_cbRate.SetCurSel(1);
	else if	(m_listPiece.GetItemText(m_nSelectedItem, 2) == _T("청소년 관람불가"))
			m_cbRate.SetCurSel(2);

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}


void CChap7PWGDlg::OnBnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strRate;

	if (m_nSelectedItem < 0)
		MessageBox(_T("수정할 작품을 선택해주세요."), _T("잠깐!"), MB_OK);
	else {
		if (m_hSelectedNode == m_hRoot) {
			bool bMovieFine = true;
			bool bDramaFine = true;
			for (int i = 0; i < m_nCount; i++) {
				if (i != m_nSelectedItem) {
					if (m_productInfo[i].strTitle == m_strTitle && m_productInfo[i].strCategory == _T("Movie")) {
						bMovieFine = false;
					}
					if (m_productInfo[i].strTitle == m_strTitle && m_productInfo[i].strCategory == _T("Drama")) {
						bDramaFine = false;
					}
				}
			}
			if (bMovieFine && bDramaFine) {
				m_productInfo[m_nSelectedItem].strTitle = m_strTitle;
				m_productInfo[m_nSelectedItem].strYear = m_strWhen;
				m_cbRate.GetLBText(m_cbRate.GetCurSel(), m_productInfo[m_nSelectedItem].strGrade);
			}

			else
				MessageBox(_T("중복된 작품이 있습니다."), _T("잠깐!"), MB_OK);
		}
		else if (m_hSelectedNode == m_hMovie) {
			bool bFine = true;
			int index = -1;

			for (int i = 0; i < m_nCount; i++) {
				if (m_productInfo[i].strCategory == _T("Movie"))
					index++;
				if (m_nSelectedItem != index &&
					m_productInfo[i].strTitle == m_strTitle &&
					m_productInfo[i].strCategory == _T("Movie")) {
					bFine = false;
				}
			}

			if (bFine) {
				int index = 0;
				for (int i = 0; i < m_nCount; i++) {
					if (m_productInfo[i].strCategory == _T("Movie")) {
						if (m_nSelectedItem == index) {
							m_productInfo[i].strTitle = m_strTitle;
							m_productInfo[i].strYear = m_strWhen;
							m_cbRate.GetLBText(m_cbRate.GetCurSel(), m_productInfo[i].strGrade);
							break;
						}
						index++;
					}
				}
			}
			else
				MessageBox(_T("중복된 작품이 있습니다."), _T("잠깐!"), MB_OK);
		}
		else if (m_hSelectedNode == m_hDrama) {
			bool bFine = true;
			int index = -1;

			for (int i = 0; i < m_nCount; i++) {
				if (m_productInfo[i].strCategory == _T("Drama"))
					index++;
				if (m_nSelectedItem != index &&
					m_productInfo[i].strTitle == m_strTitle &&
					m_productInfo[i].strCategory == _T("Drama")) {
					bFine = false;
				}
			}

			if (bFine) {
				int index = 0;
				for (int i = 0; i < m_nCount; i++) {
					if (m_productInfo[i].strCategory == _T("Drama")) {
						if (m_nSelectedItem == index) {
							m_productInfo[i].strTitle = m_strTitle;
							m_productInfo[i].strYear = m_strWhen;
							m_cbRate.GetLBText(m_cbRate.GetCurSel(), m_productInfo[i].strGrade);
							break;
						}
						index++;
					}
				}
			}
			else
				MessageBox(_T("중복된 작품이 있습니다."), _T("잠깐!"), MB_OK);
		}

		m_listPiece.DeleteAllItems();
		m_nAllCount = 0;
		m_nMovieCount = 0;
		m_nDramaCount = 0;

		for (int i = 0; i < m_nCount; i++) {
			if (m_hSelectedNode == m_hRoot) {
				m_listPiece.InsertItem(i + 1, m_productInfo[i].strTitle);
				m_listPiece.SetItem(i, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
				m_listPiece.SetItem(i, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			}
			else if (m_hSelectedNode == m_hMovie && m_productInfo[i].strCategory == _T("Movie")) {
				m_listPiece.InsertItem(m_nMovieCount + 1, m_productInfo[i].strTitle);
				m_listPiece.SetItem(m_nMovieCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
				m_listPiece.SetItem(m_nMovieCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
				m_nMovieCount++;
			}
			else if (m_hSelectedNode == m_hDrama && m_productInfo[i].strCategory == _T("Drama")) {
				m_listPiece.InsertItem(m_nDramaCount + 1, m_productInfo[i].strTitle);
				m_listPiece.SetItem(m_nDramaCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
				m_listPiece.SetItem(m_nDramaCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
				m_nDramaCount++;
			}
		}

		m_strTitle.Empty();
		m_strWhen.Empty();
		m_cbRate.SetCurSel(0);
		m_nSelectedItem = -1;
	}

	UpdateData(FALSE);
}


void CChap7PWGDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (AfxMessageBox(_T("정말 삭제하시겠습니까?"), MB_YESNO) == IDYES) {
		if (m_hSelectedNode == m_hRoot) {
			for (int i = m_nSelectedItem; i < m_nCount; i++) {
				m_productInfo[i].strCategory = m_productInfo[i + 1].strCategory;
				m_productInfo[i].strTitle = m_productInfo[i + 1].strTitle;
				m_productInfo[i].strGrade = m_productInfo[i + 1].strGrade;
				m_productInfo[i].strYear = m_productInfo[i + 1].strYear;
			}
			m_nCount--;
		}
		else if (m_hSelectedNode == m_hMovie) {
			int index = -1;
			int j = 0;

			for (j = 0; j < m_nCount; j++) {

				if (m_productInfo[j].strCategory == _T("Movie"))
					index++;
				if (m_nSelectedItem == index)
					break;
			}

			for (int i = j; i < m_nCount; i++) {
				m_productInfo[i].strCategory = m_productInfo[i + 1].strCategory;
				m_productInfo[i].strTitle = m_productInfo[i + 1].strTitle;
				m_productInfo[i].strGrade = m_productInfo[i + 1].strGrade;
				m_productInfo[i].strYear = m_productInfo[i + 1].strYear;
			}
			m_nCount--;
		}
		else if (m_hSelectedNode == m_hDrama) {
			int index = -1;
			int j = 0;

			for (j = 0; j < m_nCount; j++) {

				if (m_productInfo[j].strCategory == _T("Drama"))
					index++;
				if (m_nSelectedItem == index)
					break;
			}

			for (int i = j; i < m_nCount; i++) {
				m_productInfo[i].strCategory = m_productInfo[i + 1].strCategory;
				m_productInfo[i].strTitle = m_productInfo[i + 1].strTitle;
				m_productInfo[i].strGrade = m_productInfo[i + 1].strGrade;
				m_productInfo[i].strYear = m_productInfo[i + 1].strYear;
			}
			m_nCount--;
		}
	}

	m_listPiece.DeleteAllItems();
	m_nAllCount = 0;
	m_nMovieCount = 0;
	m_nDramaCount = 0;

	for (int i = 0; i < m_nCount; i++) {
		if (m_hSelectedNode == m_hRoot) {
			m_listPiece.InsertItem(i + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(i, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(i, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
		}
		else if (m_hSelectedNode == m_hMovie && m_productInfo[i].strCategory == _T("Movie")) {
			m_listPiece.InsertItem(m_nMovieCount + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(m_nMovieCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(m_nMovieCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			m_nMovieCount++;
		}
		else if (m_hSelectedNode == m_hDrama && m_productInfo[i].strCategory == _T("Drama")) {
			m_listPiece.InsertItem(m_nDramaCount + 1, m_productInfo[i].strTitle);
			m_listPiece.SetItem(m_nDramaCount, 1, LVIF_TEXT, m_productInfo[i].strYear, 0, 0, 0, 0);
			m_listPiece.SetItem(m_nDramaCount, 2, LVIF_TEXT, m_productInfo[i].strGrade, 0, 0, 0, 0);
			m_nDramaCount++;
		}
	}

	m_strTitle.Empty();
	m_strWhen.Empty();
	m_cbRate.SetCurSel(0);

	UpdateData(FALSE);
}
