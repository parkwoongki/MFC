#pragma once


// CColorDlg 대화 상자

class CColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CColorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderRed;
	CSliderCtrl m_sliderBlue;
	CSliderCtrl m_sliderGreen;
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	virtual BOOL OnInitDialog();
	COLORREF m_colorObject;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
