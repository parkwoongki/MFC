
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
	, m_strNum(_T(""))
	, m_strName(_T(""))
	, m_strPhone(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPWG2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ID, m_listID);
	DDX_Text(pDX, IDC_EDIT_NUM, m_strNum);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_MAJOR, m_cbMajor);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
}

BEGIN_MESSAGE_MAP(CPWG2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CPWG2Dlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPWG2Dlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPWG2Dlg::OnBnClickedButtonDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ID, &CPWG2Dlg::OnLvnItemchangedListId)
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
	LPWSTR list[4] = { _T("학번"),_T("이름"),_T("학과"), _T("전화번호") };
	int nWidth[4] = { 120, 80, 150, 170 };

	// List Control의 칼럼을 설정한다.
	for (int i = 0; i < 4; i++)
	{
		m_listID.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}

	// List Control 스타일 변경을 위한 콤보 상자의 초기 선택 값을 지정한다.
	m_listID.SetExtendedStyle(m_listID.GetExtendedStyle() |
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	((CComboBox*)GetDlgItem(IDC_COMBO_MAJOR))->SetCurSel(0);

	// 수정/삭제 버튼을 비활성화 시킨다.
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

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



void CPWG2Dlg::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int nCount = m_listID.GetItemCount();
	CString strMajor;
	m_cbMajor.GetLBText(m_cbMajor.GetCurSel(), strMajor);

	/* 등록하는데 같은 학번이 존재하는지 확인하는 작업 */
	bool bNum = false;
	CString str;
	for (int i = 0; i < nCount; i++) {
		str = m_listID.GetItemText(i, 0);
		if (str == m_strNum)
			bNum = true;
	}

	if (bNum != true) {
		if (!m_strNum.IsEmpty() && !m_strName.IsEmpty() && !m_strPhone.IsEmpty())
		{
			m_listID.InsertItem(nCount, m_strNum);
			m_listID.SetItem(nCount, 1, LVIF_TEXT, m_strName, 0, 0, 0, 0);
			m_listID.SetItem(nCount, 2, LVIF_TEXT, strMajor, 0, 0, 0, 0);
			m_listID.SetItem(nCount, 3, LVIF_TEXT, m_strPhone, 0, 0, 0, 0);

			m_strNum.Empty();
			m_strName.Empty();
			m_cbMajor.SetCurSel(0);
			m_strPhone.Empty();

			// 수정/삭제 버튼을 비활성화 시킨다.
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

			UpdateData(FALSE);
		}
		else {
			AfxMessageBox(_T("모든 항목을 입력해주세요."));
		}
	}
	else
		AfxMessageBox(_T("이미 존재하는 학번입니다."));
}


void CPWG2Dlg::OnBnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int nCount = m_listID.GetItemCount();
	CString strNum, strName, strPhone;
	strNum = m_strNum;
	strName = m_strName;
	strPhone = m_strPhone;
	CString strMajor;
	m_cbMajor.GetLBText(m_cbMajor.GetCurSel(), strMajor);

	/* 등록하는데 같은 학번이 존재하는지 확인하는 작업 (본인 학번은 제외) */
	bool bNum = false;
	CString str;
	for (int i = 0; i < nCount; i++) {
		str = m_listID.GetItemText(i, 0);
		if (i != m_nSelectedItem)
			if (str == m_strNum)
				bNum = true;
	}

	if (bNum != true) {
		if (m_nSelectedItem >= 0)
		{
			if (!m_strNum.IsEmpty() && !m_strName.IsEmpty() && !m_strPhone.IsEmpty())
			{
				m_listID.SetItem(m_nSelectedItem, 0, LVIF_TEXT, strNum, 0, 0, 0, 0);
				m_listID.SetItem(m_nSelectedItem, 1, LVIF_TEXT, strName, 0, 0, 0, 0);
				m_listID.SetItem(m_nSelectedItem, 2, LVIF_TEXT, strMajor, 0, 0, 0, 0);
				m_listID.SetItem(m_nSelectedItem, 3, LVIF_TEXT, strPhone, 0, 0, 0, 0);

				m_strNum.Empty();
				m_strName.Empty();
				m_cbMajor.SetCurSel(0);
				m_strPhone.Empty();

				((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
				((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

				UpdateData(FALSE);
			}
			else
			{
				MessageBox(_T("모든 항목을 입력해 주세요"), _T("잠깐"), MB_OK);
			}
		}
		else
		{
			MessageBox(_T("아이템을 선택하지 않았습니다."), _T("잠깐"), MB_OK);
		}
	} 
	else
		AfxMessageBox(_T("이미 존재하는 학번입니다."));
}


void CPWG2Dlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0)
	{
		m_listID.DeleteItem(m_nSelectedItem);

		m_strNum.Empty();
		m_strName.Empty();
		m_cbMajor.SetCurSel(0);
		m_strPhone.Empty();

		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("아이템을 선택하지 않았습니다."));
	}
}


void CPWG2Dlg::OnLvnItemchangedListId(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_nSelectedItem = pNMLV->iItem;

	m_strNum = m_listID.GetItemText(m_nSelectedItem, 0);
	m_strName = m_listID.GetItemText(m_nSelectedItem, 1);

	if (m_listID.GetItemText(m_nSelectedItem, 2) == _T("컴퓨터공학과"))
		m_cbMajor.SetCurSel(0);
	else if (m_listID.GetItemText(m_nSelectedItem, 2) == _T("소프트웨어공학과"))
		m_cbMajor.SetCurSel(1);
	else if (m_listID.GetItemText(m_nSelectedItem, 2) == _T("정보통신공학과"))
		m_cbMajor.SetCurSel(2);
	else if (m_listID.GetItemText(m_nSelectedItem, 2) == _T("글로컬IT학과"))
		m_cbMajor.SetCurSel(3);

	m_strPhone = m_listID.GetItemText(m_nSelectedItem, 3);

	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}
