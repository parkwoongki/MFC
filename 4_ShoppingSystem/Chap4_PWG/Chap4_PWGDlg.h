
// Chap4_PWGDlg.h: 헤더 파일
//

#pragma once


// CChap4PWGDlg 대화 상자
class CChap4PWGDlg : public CDialogEx
{
// 생성입니다.
public:
	CChap4PWGDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAP4_PWG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listLeft;
	afx_msg void OnLbnSelchangeListLeft();
	CListBox m_listRight;
	afx_msg void OnLbnSelchangeListRight();
	CComboBox m_cbMove;
	afx_msg void OnCbnSelchangeComboMove();
	CString m_strResult;
	afx_msg void OnEnChangeEditResult();
	afx_msg void OnBnClickedButtonPurchase();
};
