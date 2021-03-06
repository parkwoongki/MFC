// COvalDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Chap8_PWG.h"
#include "COvalDlg.h"
#include "afxdialogex.h"

#include "Chap8_PWGDlg.h"

// COvalDlg 대화 상자

IMPLEMENT_DYNAMIC(COvalDlg, CDialogEx)

COvalDlg::COvalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OVAL, pParent)
	, m_nHorizontal(0)
	, m_nVertical(0)
	, m_bSameRatio(FALSE)
{

}

COvalDlg::~COvalDlg()
{
}

void COvalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_HORIZONTAL, m_sliderHorizontal);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL, m_sliderVertical);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_nHorizontal);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_nVertical);
	DDX_Check(pDX, IDC_CHECK_SAME_RATIO, m_bSameRatio);
}


BEGIN_MESSAGE_MAP(COvalDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HORIZONTAL, &COvalDlg::OnNMCustomdrawSliderHorizontal)
	ON_BN_CLICKED(IDC_CHECK_SAME_RATIO, &COvalDlg::OnBnClickedCheckSameRatio)
END_MESSAGE_MAP()


// COvalDlg 메시지 처리기


BOOL COvalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_sliderHorizontal.SetRange(0, 100);
	m_sliderVertical.SetRange(0, 100);

	m_bSameRatio = true;
	((CButton*)GetDlgItem(IDC_CHECK_SAME_RATIO))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void COvalDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CChap8PWGDlg* pMainDlg = (CChap8PWGDlg*)AfxGetMainWnd();

	int nCurHScale = m_sliderHorizontal.GetPos();
	int nCurVScale = m_sliderVertical.GetPos();

	if (m_bSameRatio) {
		if (pScrollBar->GetSafeHwnd() == m_sliderHorizontal.m_hWnd) {
			m_sliderVertical.SetPos(m_sliderHorizontal.GetPos());
			m_nHorizontal = nCurHScale;
			m_nVertical = nCurHScale;
		}
		else if (pScrollBar->GetSafeHwnd() == m_sliderVertical.m_hWnd) {
			m_sliderHorizontal.SetPos(m_sliderVertical.GetPos());
			m_nHorizontal = nCurVScale;
			m_nVertical = nCurVScale;
		}
		else
			return;
		m_ptRatio.x = m_nHorizontal;
		m_ptRatio.y = m_nVertical;
	}
	else
	{
		if (pScrollBar->GetSafeHwnd() == m_sliderHorizontal.m_hWnd)
			m_nHorizontal = nCurHScale;
		else if (pScrollBar->GetSafeHwnd() == m_sliderVertical.m_hWnd)
			m_nVertical = nCurVScale;
		else
			return;
		m_ptRatio.x = nCurHScale;
		m_ptRatio.y = nCurVScale;
	}

	UpdateData(FALSE);
	pMainDlg->UpdateDrawing();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void COvalDlg::OnNMCustomdrawSliderHorizontal(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void COvalDlg::OnBnClickedCheckSameRatio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CChap8PWGDlg* pMainDlg = (CChap8PWGDlg*)AfxGetMainWnd();

	if (m_bSameRatio == TRUE)
		m_bSameRatio = false;
	else {
		if (m_sliderHorizontal.GetPos() >= m_sliderVertical.GetPos()) {
			m_sliderVertical.SetPos(m_sliderHorizontal.GetPos());
			m_nVertical = m_sliderHorizontal.GetPos();
			m_ptRatio.y = m_sliderHorizontal.GetPos();
		}
		else {
			m_sliderHorizontal.SetPos(m_sliderVertical.GetPos());
			m_nHorizontal = m_sliderVertical.GetPos();
			m_ptRatio.x = m_sliderVertical.GetPos();
		}
		
		m_bSameRatio = true;
	}

	UpdateData(FALSE);
	pMainDlg->UpdateDrawing();
}
