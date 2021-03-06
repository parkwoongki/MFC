
// Chap14_PWGDlg.h: 헤더 파일
//

#pragma once


// CChap14PWGDlg 대화 상자
class CChap14PWGDlg : public CDialogEx
{
// 생성입니다.
public:
	CChap14PWGDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTING_DIALOG };
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
	CIPAddressCtrl m_IPAddress;
	CListBox m_listChat;
	int m_nChatMode;
	CString m_strMyIP;
	CString m_strOtherIP;
	afx_msg void OnClickedRadioServer();
	afx_msg void OnRadioClient();
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();
	void ReceiveData(CString);
	void Accept(CString);
};
