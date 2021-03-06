#pragma once


// COvalDlg 대화 상자

class COvalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COvalDlg)

public:
	COvalDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~COvalDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OVAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_sliderHorizontal;
	CSliderCtrl m_sliderVertical;
	int m_nHorizontal;
	int m_nVertical;
	BOOL m_bSameRatio;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CPoint m_ptRatio;
	afx_msg void OnNMCustomdrawSliderHorizontal(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckSameRatio();
};
