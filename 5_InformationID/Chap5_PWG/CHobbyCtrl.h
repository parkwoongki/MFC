#pragma once


// CHobbyCtrl 대화 상자

class CHobbyCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CHobbyCtrl)

public:
	CHobbyCtrl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHobbyCtrl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listHobby;
	CComboBox m_cbSex;
	CString m_strName;
	virtual BOOL OnInitDialog();
	int m_nSex;
	BOOL m_bReading;
	BOOL m_bFishing;
	BOOL m_bSports;
	afx_msg void OnCbnSelchangeComboSex();
	afx_msg void OnBnClickedButtonResult();
	afx_msg void OnLbnSelchangeListHobby();
	afx_msg void OnBnClickedRadioMale();
	afx_msg void OnBnClickedRadioFemale();
	afx_msg void OnBnClickedCheckReading();
	afx_msg void OnBnClickedCheckFishing();
	afx_msg void OnBnClickedCheckSports();
};
