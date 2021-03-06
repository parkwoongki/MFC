
// Chap3_2_PWGView.cpp: CChap32PWGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chap3_2_PWG.h"
#endif

#include "Chap3_2_PWGDoc.h"
#include "Chap3_2_PWGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap32PWGView

IMPLEMENT_DYNCREATE(CChap32PWGView, CView)

BEGIN_MESSAGE_MAP(CChap32PWGView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CChap32PWGView 생성/소멸

CChap32PWGView::CChap32PWGView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bDrag = false;
}

CChap32PWGView::~CChap32PWGView()
{
}

BOOL CChap32PWGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CChap32PWGView 그리기

void CChap32PWGView::OnDraw(CDC* pDC)
{
	CChap32PWGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(m_ptLocation.x, m_ptLocation.y, m_strOutput);
}


// CChap32PWGView 인쇄

BOOL CChap32PWGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CChap32PWGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CChap32PWGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CChap32PWGView 진단

#ifdef _DEBUG
void CChap32PWGView::AssertValid() const
{
	CView::AssertValid();
}

void CChap32PWGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap32PWGDoc* CChap32PWGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap32PWGDoc)));
	return (CChap32PWGDoc*)m_pDocument;
}
#endif //_DEBUG


// CChap32PWGView 메시지 처리기


void CChap32PWGView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int nCharIndex;
	nCharIndex = m_strOutput.GetLength();

	if (nChar == VK_BACK)
		m_strOutput.Delete(nCharIndex - 1, 1);
	else
		m_strOutput += (WCHAR)nChar;

	Invalidate();

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CChap32PWGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:
		m_ptLocation.x--;
		break;
	case VK_RIGHT:
		m_ptLocation.x++;
		break;
	case VK_UP:
		m_ptLocation.y--;
		break;
	case VK_DOWN:
		m_ptLocation.y++;
		break;
	case VK_PRIOR:
		m_ptLocation.y += 50;
		break;
	case VK_NEXT:
		m_ptLocation.y -= 50;
		break;
	case VK_HOME:
		m_ptLocation = CPoint(0, 0);
		break;
	}

	if (m_ptLocation.x < 0) {
		m_ptLocation.x = 0;
		AfxMessageBox(_T("왼쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y < 0) {
		m_ptLocation.y = 0;
		AfxMessageBox(_T("위쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.x > m_ptClientSize.x) {
		m_ptLocation.x = m_ptClientSize.x;
		AfxMessageBox(_T("오른쪽으로 더 이상 이동할 수 없습니다."));
	}
	if (m_ptLocation.y > m_ptClientSize.y) {
		m_ptLocation.y = m_ptClientSize.y;
		AfxMessageBox(_T("아래쪽으로 더 이상 이동할 수 없습니다."));
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChap32PWGView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ptClientSize.x = cx;
	m_ptClientSize.y = cy;

	Invalidate();
}


void CChap32PWGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptLocation.x = point.x;
	m_ptLocation.y = point.y;
	m_bDrag = true;

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CChap32PWGView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_strOutput.IsEmpty() == false) {
		if (AfxMessageBox(_T("문자를 지우시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES);
		m_strOutput.Empty();
	}
	else
		AfxMessageBox(_T("문자를 입력하시오."));

	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CChap32PWGView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bDrag = false; /// 버튼 업 되면 false 집어넣음

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CChap32PWGView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
		m_ptLocation = point; /// 드래그 true(좌클릭된 상태에서 마우스 드래그)에서 현재 좌표 넣기

	Invalidate();

	CView::OnMouseMove(nFlags, point);
}
