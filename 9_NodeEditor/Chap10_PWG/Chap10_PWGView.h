
// Chap10_PWGView.h: CChap10PWGView 클래스의 인터페이스
//

#pragma once


class CChap10PWGView : public CTreeView
{
protected: // serialization에서만 만들어집니다.
	CChap10PWGView() noexcept;
	DECLARE_DYNCREATE(CChap10PWGView)

// 특성입니다.
public:
	CChap10PWGDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CChap10PWGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	HTREEITEM m_hRoot;
	HTREEITEM m_hSelectedNode;
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	//CTreeCtrl& m_treeCtrl;
};

#ifndef _DEBUG  // Chap10_PWGView.cpp의 디버그 버전
inline CChap10PWGDoc* CChap10PWGView::GetDocument() const
   { return reinterpret_cast<CChap10PWGDoc*>(m_pDocument); }
#endif

