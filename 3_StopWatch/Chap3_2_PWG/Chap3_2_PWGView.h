
// Chap3_2_PWGView.h: CChap32PWGView 클래스의 인터페이스
//

#pragma once


class CChap32PWGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CChap32PWGView() noexcept;
	DECLARE_DYNCREATE(CChap32PWGView)

// 특성입니다.
public:
	CChap32PWGDoc* GetDocument() const;

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
	virtual ~CChap32PWGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	CString m_strOutput;
	CPoint m_ptLocation;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	CPoint m_ptClientSize;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
	bool m_bDrag;
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Chap3_2_PWGView.cpp의 디버그 버전
inline CChap32PWGDoc* CChap32PWGView::GetDocument() const
   { return reinterpret_cast<CChap32PWGDoc*>(m_pDocument); }
#endif

