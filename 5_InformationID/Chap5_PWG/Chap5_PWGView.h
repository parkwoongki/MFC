
// Chap5_PWGView.h: CChap5PWGView 클래스의 인터페이스
//

#pragma once


class CChap5PWGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CChap5PWGView();
	DECLARE_DYNCREATE(CChap5PWGView)

// 특성입니다.
public:
	CChap5PWGDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CChap5PWGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strSex;
	CString m_strHobby;
};

#ifndef _DEBUG  // Chap5_PWGView.cpp의 디버그 버전
inline CChap5PWGDoc* CChap5PWGView::GetDocument() const
   { return reinterpret_cast<CChap5PWGDoc*>(m_pDocument); }
#endif

