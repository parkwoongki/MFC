
// Chap3_1_PWGView.h: CChap31PWGView 클래스의 인터페이스
//

#pragma once


class CChap31PWGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CChap31PWGView() noexcept;
	DECLARE_DYNCREATE(CChap31PWGView)

// 특성입니다.
public:
	CChap31PWGDoc* GetDocument() const;

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
	virtual ~CChap31PWGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	CString m_strStopWatch;
	CString m_strRecord[40];
	int m_nCount;
	int m_nMinute;
	int m_nSecond;
	int m_nMSec;
	bool m_bStopWatchRun;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // Chap3_1_PWGView.cpp의 디버그 버전
inline CChap31PWGDoc* CChap31PWGView::GetDocument() const
   { return reinterpret_cast<CChap31PWGDoc*>(m_pDocument); }
#endif

