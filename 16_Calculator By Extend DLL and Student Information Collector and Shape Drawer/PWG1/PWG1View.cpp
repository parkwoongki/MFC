
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
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPWG1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CPWG1View::OnLine)
	ON_COMMAND(ID_RECT, &CPWG1View::OnRect)
	ON_COMMAND(ID_ELLIPSE, &CPWG1View::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_RED_PEN, &CPWG1View::OnRedPen)
	ON_COMMAND(ID_GREEN_PEN, &CPWG1View::OnGreenPen)
	ON_COMMAND(ID_BLUE_PEN, &CPWG1View::OnBluePen)
	ON_COMMAND(ID_RED_BRUSH, &CPWG1View::OnRedBrush)
	ON_COMMAND(ID_GREEN_BRUSH, &CPWG1View::OnGreenBrush)
	ON_COMMAND(ID_BLUE_BRUSH, &CPWG1View::OnBlueBrush)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CPWG1View::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CPWG1View::OnUpdateRect)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CPWG1View::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_RED_PEN, &CPWG1View::OnUpdateRedPen)
	ON_UPDATE_COMMAND_UI(ID_GREEN_PEN, &CPWG1View::OnUpdateGreenPen)
	ON_UPDATE_COMMAND_UI(ID_BLUE_PEN, &CPWG1View::OnUpdateBluePen)
	ON_UPDATE_COMMAND_UI(ID_RED_BRUSH, &CPWG1View::OnUpdateRedBrush)
	ON_UPDATE_COMMAND_UI(ID_GREEN_BRUSH, &CPWG1View::OnUpdateGreenBrush)
	ON_UPDATE_COMMAND_UI(ID_BLUE_BRUSH, &CPWG1View::OnUpdateBlueBrush)
END_MESSAGE_MAP()

// CPWG1View 생성/소멸

CPWG1View::CPWG1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nDrawMode = 0;
	m_colorPen = RGB(255, 0, 0);
	m_colorBrush = RGB(255, 0, 0);
	m_ptStart = 0;
	m_ptPrev = 0;
	m_bFirst = false;
	m_bLButtonDown = false;
	m_nCount = 0;
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
	UpdateData(TRUE);

	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen); 		// pen 객체 생성
	oldpen = pDC->SelectObject(&pen);			// pen 객체 등록
	pDC->SetROP2(R2_COPYPEN);			// COPYPEN으로 설정
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(m_colorBrush);
	oldbrush = pDC->SelectObject(&brush);			// brush 객체 등록

	switch (m_nDrawMode)
	{
	case 0:					// 직선 그리기
									//마지막 직선 그림
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case 1:
		pDC->Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case 2:					// 원 그리기
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	}
	//Invalidate(FALSE);
	pDC->SelectObject(oldpen);			//이전 pen으로 설정
	pDC->SelectObject(oldbrush);			//이전 brush으로 설정
	pen.DeleteObject();				//pen 객체 삭제
	brush.DeleteObject();			//brush 객체 삭제
}


// CPWG1View 인쇄


void CPWG1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

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

void CPWG1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPWG1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
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


void CPWG1View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 0;
}


void CPWG1View::OnRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 1;
}


void CPWG1View::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 2;
}


void CPWG1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(FALSE);

	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_bFirst = true;
		m_nCount = 0;
		Invalidate(false);			//화면갱신
	}
	switch (m_nDrawMode)
	{
	case 0:	//직선그리기
	case 1:
	case 2:			//원 그리기
		m_bLButtonDown = true; 		//왼쪽버튼이 눌림
		m_ptStart = m_ptPrev = point; 	//시작점과 이전 점에 현재 점을 저장
		m_bFirst = false;			//처음 그리는 것 -> false
		break;
	}

	RECT rectClient;				//구조체 변수 선언
	SetCapture();				//마우스 캡쳐
	GetClientRect(&rectClient);		//클라이언트 영역 받음
	ClientToScreen(&rectClient);		//스크린 좌표계 변환
	::ClipCursor(&rectClient);			//마우스 이동범위를 클라이언트 영역으로 제한

	UpdateData(FALSE);

	CView::OnLButtonDown(nFlags, point);
}


void CPWG1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	CClientDC dc(this);				//클라이언트 객체 얻음
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);		//Pen 객체 생성
	oldpen = dc.SelectObject(&pen);			//pen 객체 등록	

	dc.SetROP2(R2_NOTXORPEN);			//R2_NOTXORPEN으로 설정

	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(m_colorBrush);
	oldbrush = dc.SelectObject(&brush);			//brush 객체 등록

	switch (m_nDrawMode)
	{
	case 0:				//직선 그리기
		if (m_bLButtonDown)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);			//이전 직선 지움
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);				//현재 직선 그림
			m_ptPrev = point;			//이전 점에 현재 점을 저장
		}
		break;
	case 1:
		if (m_bLButtonDown)
		{
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;			//이전 점에 현재 점을 저장
		}
		break;
	case 2:				//원 그리기
		if (m_bLButtonDown)
		{
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;			//이전 점에 현재 점을 저장
		}
		break;
	}

	UpdateData(FALSE);

	CView::OnMouseMove(nFlags, point);
}


void CPWG1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	if (m_bLButtonDown)			//왼쪽 마우스 버튼이 눌린 상태이면
	{
		//그리기 모드가 직선 그리기, 원 그리기 이면
		if (m_nDrawMode == 0 || m_nDrawMode == 1 || m_nDrawMode == 2)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();		//마우스 캡쳐 해제
			::ClipCursor(NULL);	//마우스 클립 해제
			Invalidate(false);		//화면 갱신
		}
	}
	UpdateData(FALSE);

	CView::OnLButtonUp(nFlags, point);
}


void CPWG1View::OnRedPen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorPen = RGB(255, 0, 0);
}


void CPWG1View::OnGreenPen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorPen = RGB(0, 255, 0);
}


void CPWG1View::OnBluePen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorPen = RGB(0, 0, 255);
}


void CPWG1View::OnRedBrush()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorBrush = RGB(255, 0, 0);
}


void CPWG1View::OnGreenBrush()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorBrush = RGB(0, 255, 0);
}


void CPWG1View::OnBlueBrush()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_colorBrush = RGB(0, 0, 255);
}


void CPWG1View::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == 0 ? 1 : 0);
}


void CPWG1View::OnUpdateRect(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == 1? 1 : 0);
}


void CPWG1View::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == 2 ? 1 : 0);
}


void CPWG1View::OnUpdateRedPen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorPen == RGB(255,0,0) ? 1 : 0);
}


void CPWG1View::OnUpdateGreenPen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorPen == RGB(0, 255, 0) ? 1 : 0);
}


void CPWG1View::OnUpdateBluePen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorPen == RGB(0, 0, 255) ? 1 : 0);
}


void CPWG1View::OnUpdateRedBrush(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorBrush == RGB(255, 0, 0) ? 1 : 0);
}


void CPWG1View::OnUpdateGreenBrush(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorBrush == RGB(0, 255, 0) ? 1 : 0);
}


void CPWG1View::OnUpdateBlueBrush(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_colorBrush == RGB(0, 0, 255) ? 1 : 0);
}
