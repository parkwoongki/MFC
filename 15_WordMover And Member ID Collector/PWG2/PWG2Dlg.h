
// PWG2Dlg.h: 헤더 파일
//

#pragma once


// CPWG2Dlg 대화 상자
class CPWG2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CPWG2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PWG2_DIALOG };
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
	CString m_strName;
	int m_nGender;
	CComboBox m_cbAge;
	BOOL m_bSubject1;
	BOOL m_bSubject2;
	BOOL m_bSubject3;
	BOOL m_bSubject4;
	afx_msg void OnBnClickedButtonJoin();
	CListBox m_listInfo;
	afx_msg void OnLbnSelchangeListInfo();
	afx_msg void OnBnClickedButtonWithdrawal();
};
