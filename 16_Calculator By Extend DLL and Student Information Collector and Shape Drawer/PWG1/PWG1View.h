
// PWG1View.h: CPWG1View 클래스의 인터페이스
//

#pragma once


class CPWG1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPWG1View() noexcept;
	DECLARE_DYNCREATE(CPWG1View)

// 특성입니다.
public:
	CPWG1Doc* GetDocument() const;

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
	virtual ~CPWG1View();
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
	COLORREF m_colorPen;
	COLORREF m_colorBrush;
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnEllipse();
	int m_nDrawMode;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bFirst;
	bool m_bLButtonDown;
	bool m_bContextMenu;
	bool m_bHatch;
	int m_nCount;
	afx_msg void OnRedPen();
	afx_msg void OnGreenPen();
	afx_msg void OnBluePen();
	afx_msg void OnRedBrush();
	afx_msg void OnGreenBrush();
	afx_msg void OnBlueBrush();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRedPen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGreenPen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBluePen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRedBrush(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGreenBrush(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlueBrush(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // PWG1View.cpp의 디버그 버전
inline CPWG1Doc* CPWG1View::GetDocument() const
   { return reinterpret_cast<CPWG1Doc*>(m_pDocument); }
#endif

