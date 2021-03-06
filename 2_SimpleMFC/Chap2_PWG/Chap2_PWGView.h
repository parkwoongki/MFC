
// Chap2_PWGView.h: CChap2PWGView 클래스의 인터페이스
//

#pragma once


class CChap2PWGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CChap2PWGView();
	DECLARE_DYNCREATE(CChap2PWGView)

// 특성입니다.
public:
	CChap2PWGDoc* GetDocument() const;

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
	virtual ~CChap2PWGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	CString m_strWindowSize;
	CString m_strOutput;
	CPoint m_ptMousePoint;
	CString m_strPointText;
	bool m_bDrag;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // Chap2_PWGView.cpp의 디버그 버전
inline CChap2PWGDoc* CChap2PWGView::GetDocument() const
   { return reinterpret_cast<CChap2PWGDoc*>(m_pDocument); }
#endif

