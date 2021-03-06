
// Chap7_PWGDlg.h: 헤더 파일
//

enum { MOVIE, DRAMA };

typedef struct Product {
	CString strCategory;
	CString strTitle;
	CString strYear;
	CString strGrade;
}Product;
#pragma once


// CChap7PWGDlg 대화 상자
class CChap7PWGDlg : public CDialogEx
{
// 생성입니다.
public:
	CChap7PWGDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAP7_PWG_DIALOG };
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
	CTreeCtrl m_treeGenre;
	CListCtrl m_listPiece;
	HTREEITEM m_hRoot;
	HTREEITEM m_hSelectedNode;
	Product m_productInfo[50];
	int m_nCount;
	HTREEITEM m_hMovie;
	HTREEITEM m_hDrama;
	CString m_strTitle;
	CString m_strWhen;
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnTvnSelchangedTreeGenre(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPiece(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nSelectedItem;
	CComboBox m_cbRate;
	afx_msg void OnBnClickedButtonModify();
	int m_nMovieCount;
	int m_nDramaCount;
	int m_nAllCount;
	afx_msg void OnBnClickedButtonDelete();
};
