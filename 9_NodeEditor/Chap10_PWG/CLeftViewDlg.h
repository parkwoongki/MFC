
// CLeftViewDlg 대화 상자


#pragma once


class CLeftViewDlg : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CLeftViewDlg() noexcept;
	DECLARE_DYNCREATE(CLeftViewDlg)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

	// 특성입니다.
public:
	CChap10PWGDoc * GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

									// 구현입니다.
public:
	virtual ~CLeftViewDlg();
	CString m_strNodeText;
	CString m_strSelectedNode;
	bool m_bChecked;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonModify();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedCheckExpand();
};

#ifndef _DEBUG  // MFCApplication5View.cpp의 디버그 버전
inline CChap10PWGDoc* CChap10PWGDoc::GetDocument() const
{
	return reinterpret_cast<CChap10PWGDoc*>(m_pDocument);
}
#endif
