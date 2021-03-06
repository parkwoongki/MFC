
// PWG1View.cpp: CPWG1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PWG1.h"
#endif

#include "PWG1Doc.h"
#include "PWG1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPWG1View

IMPLEMENT_DYNCREATE(CPWG1View, CView)

BEGIN_MESSAGE_MAP(CPWG1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPWG1View 생성/소멸

CPWG1View::CPWG1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptStrPoint = 0;
}

CPWG1View::~CPWG1View()
{
}

BOOL CPWG1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPWG1View 그리기

void CPWG1View::OnDraw(CDC* pDC)
{
	CPWG1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->TextOut(m_ptStrPoint.x, m_ptStrPoint.y, m_strOutput);
}


// CPWG1View 인쇄

BOOL CPWG1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPWG1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPWG1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPWG1View 진단

#ifdef _DEBUG
void CPWG1View::AssertValid() const
{
	CView::AssertValid();
}

void CPWG1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPWG1Doc* CPWG1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPWG1Doc)));
	return (CPWG1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPWG1View 메시지 처리기


void CPWG1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();

	if (nChar == VK_BACK)
		m_strOutput.Delete(nCharIndex - 1, 1);
	else
		m_strOutput += (WCHAR)nChar;

	m_strOutput.TrimRight(VK_RETURN);

	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPWG1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_RETURN:
		SetTimer(0, 500, NULL);
		break;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPWG1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_ptStrPoint.x < m_ptClientSize.x) {
		m_ptStrPoint.x += 50;
	}
	else {
		m_ptStrPoint.x = 0;
	}
	
	//m_ptStrPoint.y += 50;

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CPWG1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;
}


void CPWG1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptStrPoint.x = point.x-50;
	m_ptStrPoint.y = point.y;

	CView::OnLButtonDown(nFlags, point);
}


void CPWG1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strOutput.IsEmpty())
		AfxMessageBox(_T("문자열을 입력하시오."));
	else {
		if (AfxMessageBox(_T("문자를 모두 지우시겠습니까?"), MB_ICONQUESTION | MB_YESNO) == IDYES) {
			m_strOutput.Empty();
			m_ptStrPoint.x = 0;
			m_ptStrPoint.y = 0;
			KillTimer(0);
		}
	}
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}
