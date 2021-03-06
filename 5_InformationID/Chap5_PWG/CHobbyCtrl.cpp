// CHobbyCtrl.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap5_PWG.h"
#include "CHobbyCtrl.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "Chap5_PWGDoc.h"
#include "Chap5_PWGView.h"



// CHobbyCtrl 대화 상자

IMPLEMENT_DYNAMIC(CHobbyCtrl, CDialogEx)

CHobbyCtrl::CHobbyCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strName(_T(""))
	, m_nSex(0)
	, m_bReading(FALSE)
	, m_bFishing(FALSE)
	, m_bSports(FALSE)
{

}

CHobbyCtrl::~CHobbyCtrl()
{
}

void CHobbyCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOBBY, m_listHobby);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Radio(pDX, IDC_RADIO_MALE, m_nSex);
	DDX_Check(pDX, IDC_CHECK_READING, m_bReading);
	DDX_Check(pDX, IDC_CHECK_FISHING, m_bFishing);
	DDX_Check(pDX, IDC_CHECK_SPORTS, m_bSports);
}


BEGIN_MESSAGE_MAP(CHobbyCtrl, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CHobbyCtrl::OnCbnSelchangeComboSex)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CHobbyCtrl::OnBnClickedButtonResult)
	ON_LBN_SELCHANGE(IDC_LIST_HOBBY, &CHobbyCtrl::OnLbnSelchangeListHobby)
	ON_BN_CLICKED(IDC_RADIO_MALE, &CHobbyCtrl::OnBnClickedRadioMale)
	ON_BN_CLICKED(IDC_RADIO_FEMALE, &CHobbyCtrl::OnBnClickedRadioFemale)
	ON_BN_CLICKED(IDC_CHECK_READING, &CHobbyCtrl::OnBnClickedCheckReading)
	ON_BN_CLICKED(IDC_CHECK_FISHING, &CHobbyCtrl::OnBnClickedCheckFishing)
	ON_BN_CLICKED(IDC_CHECK_SPORTS, &CHobbyCtrl::OnBnClickedCheckSports)
END_MESSAGE_MAP()


// CHobbyCtrl 메시지 처리기


BOOL CHobbyCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_listHobby.AddString(_T("독서"));
	m_listHobby.AddString(_T("낚시"));
	m_listHobby.AddString(_T("운동"));

	m_cbSex.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHobbyCtrl::OnCbnSelchangeComboSex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int index = m_cbSex.GetCurSel();
	
	switch (index) {
	case 0: 
		m_nSex = 0;
		break;
	case 1:
		m_nSex = 1;
		break;
	}

	UpdateData(FALSE);
}



void CHobbyCtrl::OnBnClickedButtonResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(true);
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CChap5PWGView* pView = (CChap5PWGView*)pFrame->GetActiveView();
	
	pView->m_strName = _T("이름 : ") + m_strName;
	pView->m_strHobby = _T("내가 선택한 취미 : ");
	pView->m_strSex = _T("성별 : ");

	switch (m_nSex) {
	case 0:
		pView->m_strSex += _T("남자");
		break;
	case 1:
		pView->m_strSex += _T("여자");
		break;
	}

	if (m_bReading == TRUE) {
		pView->m_strHobby += _T("독서 ");
	}
	else {

	}
	if (m_bFishing == TRUE) {
		m_listHobby.SetCurSel(1);
		pView->m_strHobby += _T("낚시 ");
	}
	if (m_bSports == TRUE) {
		m_listHobby.SetCurSel(2);
		pView->m_strHobby += _T("운동 ");
	}

	if ((pView->m_strName == _T("이름 : ")) ||
		(pView->m_strHobby == _T("내가 선택한 취미 : ")) ||
		(pView->m_strSex == _T("성별 : ")))
	{
		AfxMessageBox(_T("모든 항목을 기입해주세요."));
	}
	else {
		UpdateData(false);
		pView->Invalidate();
	}
}


void CHobbyCtrl::OnLbnSelchangeListHobby()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int index = m_listHobby.GetCurSel();

	switch (index) {
	case 0:
		if (m_bReading == FALSE) {
			m_bReading = TRUE;
		}
		else if (m_bReading == TRUE) {
			((CButton*)GetDlgItem(IDC_CHECK_READING))->SetCheck(FALSE);
			m_bReading = FALSE;
		}
		break;
	case 1:
		if (m_bFishing == FALSE) {
			m_bFishing = TRUE;
		}
		else if (m_bFishing == TRUE) {
			((CButton*)GetDlgItem(IDC_CHECK_FISHING))->SetCheck(FALSE);
			m_bFishing = FALSE;
		}
		break;
	case 2:
		if (m_bSports == FALSE) {
			m_bSports = TRUE;
		}
		else if (m_bSports == TRUE) {
			((CButton*)GetDlgItem(IDC_CHECK_SPORTS))->SetCheck(FALSE);
			m_bSports = FALSE;
		}
		break;
	}


	UpdateData(FALSE);
}


void CHobbyCtrl::OnBnClickedRadioMale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	switch (m_nSex) {
	case 0:
		m_cbSex.SetCurSel(0);
		break;
	}
	UpdateData(false);
}


void CHobbyCtrl::OnBnClickedRadioFemale()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	switch (m_nSex) {
	case 1:
		m_cbSex.SetCurSel(1);
		break;
	}
	UpdateData(false);
}


void CHobbyCtrl::OnBnClickedCheckReading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (m_bReading == TRUE) {
		m_listHobby.SetSel(0);
	}
	else {
		m_listHobby.SetSel(0, false);
	}
}


void CHobbyCtrl::OnBnClickedCheckFishing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (m_bFishing == TRUE) {
		m_listHobby.SetSel(1);
	}
	else {
		m_listHobby.SetSel(1, false);
	}
}


void CHobbyCtrl::OnBnClickedCheckSports()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (m_bSports == TRUE) {
		m_listHobby.SetSel(2);
	}
	else {
		m_listHobby.SetSel(2, false);
	}
}
