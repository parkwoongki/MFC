
// Chap2_PWGView.cpp: CChap2PWGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chap2_PWG.h"
#endif

#include "Chap2_PWGDoc.h"
#include "Chap2_PWGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap2PWGView

IMPLEMENT_DYNCREATE(CChap2PWGView, CView)

BEGIN_MESSAGE_MAP(CChap2PWGView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CChap2PWGView 생성/소멸

CChap2PWGView::CChap2PWGView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CChap2PWGView::~CChap2PWGView()
{
}

BOOL CChap2PWGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CChap2PWGView 그리기

void CChap2PWGView::OnDraw(CDC* pDC)
{
	CChap2PWGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(10, 10, m_strWindowSize);
	pDC->TextOut(m_ptMousePoint.x, m_ptMousePoint.y, m_strPointText);

	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText(m_strOutput, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CChap2PWGView 인쇄

BOOL CChap2PWGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CChap2PWGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CChap2PWGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CChap2PWGView 진단

#ifdef _DEBUG
void CChap2PWGView::AssertValid() const
{
	CView::AssertValid();
}

void CChap2PWGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap2PWGDoc* CChap2PWGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap2PWGDoc)));
	return (CChap2PWGDoc*)m_pDocument;
}
#endif //_DEBUG


// CChap2PWGView 메시지 처리기


void CChap2PWGView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_strWindowSize.Format(_T("윈도우 크기는 넓이 %d, 높이 %d입니다."), cx, cy );
	Invalidate();
}


void CChap2PWGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("왼쪽 마우스를 눌렀습니다.");
	m_bDrag = TRUE;
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CChap2PWGView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("왼쪽 마우스가 떼어졌습니다.");
	m_bDrag = FALSE;
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CChap2PWGView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("오른쪽 마우스를 눌렀습니다.");
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CChap2PWGView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("오른쪽 마우스가 떼어졌습니다.");
	Invalidate();

	CView::OnRButtonUp(nFlags, point);
}


void CChap2PWGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("키보드를 눌렀습니다.");
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChap2PWGView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_strOutput = _T("키보드가 떼어졌습니다.");
	Invalidate();

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CChap2PWGView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag == TRUE)
		m_strOutput = _T("마우스를 드래그하고 있습니다.");
	else
		m_strOutput = _T("마우스가 이동 중 입니다.");

	m_ptMousePoint = point;
	m_strPointText.Format(_T("    X : %d Y : %d"), point.x, point.y);
	Invalidate();

	CView::OnMouseMove(nFlags, point);
}
