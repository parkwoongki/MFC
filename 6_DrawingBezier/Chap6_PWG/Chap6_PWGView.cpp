
// Chap6_PWGView.cpp: CChap6PWGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chap6_PWG.h"
#endif

#include "Chap6_PWGDoc.h"
#include "Chap6_PWGView.h"
#include "Chap6_PWGDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap6PWGView

IMPLEMENT_DYNCREATE(CChap6PWGView, CView)

BEGIN_MESSAGE_MAP(CChap6PWGView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChap6PWGView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ELLIPSE, &CChap6PWGView::OnEllipse)
	ON_COMMAND(ID_LINE, &CChap6PWGView::OnLine)
	ON_COMMAND(ID_POLYGON, &CChap6PWGView::OnPolygon)
	ON_COMMAND(ID_BDIAGONAL, &CChap6PWGView::OnBdiagonal)
	ON_COMMAND(ID_CROSS, &CChap6PWGView::OnCross)
	ON_COMMAND(ID_VERTICAL, &CChap6PWGView::OnVertical)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CChap6PWGView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CChap6PWGView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CChap6PWGView::OnUpdatePolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_LINE_COLOR, &CChap6PWGView::OnLineColor)
	ON_COMMAND(ID_FACE_COLOR, &CChap6PWGView::OnFaceColor)
	ON_COMMAND(ID_BEZIER, &CChap6PWGView::OnBezier)
	ON_UPDATE_COMMAND_UI(ID_BEZIER, &CChap6PWGView::OnUpdateBezier)
END_MESSAGE_MAP()

// CChap6PWGView 생성/소멸

CChap6PWGView::CChap6PWGView()
	: m_nDrawMode(0)
	, m_nHatchStyle(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	, m_bFirst(0)
	, m_bLButtonDown(false)
	, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nDrawMode = LINE_MODE;
	m_bContextMenu = true;
	m_bFirst = true;
	m_bLButtonDown = false;
	m_nCount = 0;
	for (int i = 0; i < 50; i++)
		m_ptData[i] = 0;
	m_bHatch = false;
	m_nHatchStyle = HS_CROSS;
	m_colorPen = RGB(0, 0, 0);
	m_colorBrush = RGB(255, 255, 255);
	m_bBezierDraw = false;
}

CChap6PWGView::~CChap6PWGView()
{
}

BOOL CChap6PWGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CChap6PWGView 그리기

void CChap6PWGView::OnDraw(CDC* pDC)
{
	CChap6PWGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen, *oldpen, redpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	redpen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldpen = pDC->SelectObject(&pen);

	pDC->SetROP2(R2_COPYPEN);					// R2_COPYPEN으로 생성

	CBrush brush, *oldbrush, graybrush;

	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);
	else
		brush.CreateSolidBrush(m_colorBrush);

	graybrush.CreateSolidBrush(RGB(200,200,200));

	oldbrush = pDC->SelectObject(&brush);

	switch (m_nDrawMode) {
	case LINE_MODE :
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE :
		pDC->Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case POLYGON_MODE:
		pDC->Polygon(m_ptData, m_nCount);
		break;	
	case BEZIER_MODE:
		for (int i = 0; i < m_nCount ; i++) {
			pDC->SelectObject(&graybrush);
			pDC->Ellipse(m_ptData[i].x - 5, m_ptData[i].y - 5, m_ptData[i].x + 5, m_ptData[i].y + 5);
		}
		pDC->Polyline(m_ptData, m_nCount);
		pDC->SelectObject(&redpen);
		if (m_bBezierDraw == true) {
			pDC->PolyBezier(m_ptData, m_nCount);
			m_bBezierDraw = false;
		}
		break;
	}
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();
	redpen.DeleteObject();
	graybrush.DeleteObject();
}


// CChap6PWGView 인쇄


void CChap6PWGView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChap6PWGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CChap6PWGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CChap6PWGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CChap6PWGView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChap6PWGView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	if (m_bContextMenu == true)
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	m_bContextMenu = true;
#endif
}


// CChap6PWGView 진단

#ifdef _DEBUG
void CChap6PWGView::AssertValid() const
{
	CView::AssertValid();
}

void CChap6PWGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap6PWGDoc* CChap6PWGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap6PWGDoc)));
	return (CChap6PWGDoc*)m_pDocument;
}
#endif //_DEBUG


// CChap6PWGView 메시지 처리기



void CChap6PWGView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = LINE_MODE;
}


void CChap6PWGView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = ELLIPSE_MODE;
} 


void CChap6PWGView::OnPolygon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = POLYGON_MODE;
}


void CChap6PWGView::OnBezier()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = BEZIER_MODE;
}


void CChap6PWGView::OnBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_BDIAGONAL;
	m_bHatch = true;
	Invalidate();
}


void CChap6PWGView::OnCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_CROSS;
	m_bHatch = true;
	Invalidate();
}


void CChap6PWGView::OnVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nHatchStyle = HS_VERTICAL;
	m_bHatch = true;
	Invalidate();
}


void CChap6PWGView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == LINE_MODE ? true : false); // 레디오랑 쳌 둘 다 가능
}


void CChap6PWGView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == ELLIPSE_MODE ? true : false);
}


void CChap6PWGView::OnUpdatePolygon(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == POLYGON_MODE ? true : false);
}


void CChap6PWGView::OnUpdateBezier(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nDrawMode == BEZIER_MODE ? true : false);
}


void CChap6PWGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bFirst) {
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_bFirst = true;
		m_nCount = 0;
		for (int i = 0; i < 50; i++)
			m_ptData[i] = 0;
		Invalidate(true);
	}

	switch (m_nDrawMode) {
	case LINE_MODE : 
	case ELLIPSE_MODE :
		m_bLButtonDown = true;
		m_ptStart = m_ptPrev = point;
		m_bFirst = false;
		break;
	case POLYGON_MODE :
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		break;
	case BEZIER_MODE:
		if (m_bFirst == true)
			m_bFirst = false;
		m_ptStart = m_ptPrev = point;
		m_ptData[m_nCount] = point;
		m_nCount++;
		Invalidate(true);
		break;
	}

	RECT rectClient;
	SetCapture();
	GetClientRect(&rectClient);
	ClientToScreen(&rectClient);
	::ClipCursor(&rectClient);

	CView::OnLButtonDown(nFlags, point);
}


void CChap6PWGView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);

	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID, 1, m_colorPen);
	oldpen = dc.SelectObject(&pen);

	dc.SetROP2(R2_NOTXORPEN);					// R@_NOTXORPEN으로 생성

	CBrush brush, *oldbrush;

	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_colorBrush);
	else
		brush.CreateSolidBrush(m_colorBrush);

	oldbrush = dc.SelectObject(&brush);

	switch (m_nDrawMode) {
	case LINE_MODE:
		if (m_bLButtonDown) {
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);	// 이전 직선 지우기
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);	// 현재 직선 그림
			m_ptPrev = point;	// 이전 점에 현재 점을 저장
		}
		break;
	case ELLIPSE_MODE:
		if (m_bLButtonDown) {
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y); // 시작
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y); // 끝
			m_ptPrev = point;	// 이전 점에 현재 점을 저장
		}
		break;
	case POLYGON_MODE:
		if (!m_bFirst) {
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);	// 이전 직선 지우기
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);	// 현재 직선 그림
			m_ptPrev = point;	// 이전 점에 현재 점을 저장
		}
		break;
	case BEZIER_MODE:
		if (!m_bFirst) {
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);	// 이전 직선 지우기
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);	// 현재 직선 그림
			m_ptPrev = point;	// 이전 점에 현재 점을 저장
		}
		break;
	}

	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("마우스 위치 : x : %d, y : %d"), point.x, point.y);

	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);

	CView::OnMouseMove(nFlags, point);
}


void CChap6PWGView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown) {
		// 그리기 모드가 직선 그리기, 원 그리기 이면
		if (m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE) {
			m_bLButtonDown = false;
			m_bFirst = true;
			ReleaseCapture();	// 마우스 캡처 해제
			::ClipCursor(NULL); // 마우스 클립 해제
			Invalidate();       // 화면 갱신
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CChap6PWGView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 다각형 그리기
	if (m_nDrawMode == POLYGON_MODE) {
		if (!m_bFirst) {
			m_bContextMenu = FALSE; // 컨텍스트 메뉴 비활성
			// 배열에 현재점을 저장하고 카운트 증가
			m_ptData[m_nCount] = point;
			m_nCount++;	
			//m_ptData[m_nCount] == m_ptStart;
			// 체크변수 초기화 -> 다시 다각형을 그리기 위해
			m_bFirst = TRUE;
			ReleaseCapture();
			::ClipCursor(NULL);
			Invalidate(TRUE);
		}
	}
	else if (m_nDrawMode == BEZIER_MODE) {
		if (!m_bFirst) {
			if ((m_nCount) % 3 != 0 || m_nCount ==1) {
				AfxMessageBox(_T("점의 수 오류 <점의 수 = 베이지 곡선수*3+1>"));
			}
			else {
				m_bContextMenu = FALSE; // 컨텍스트 메뉴 비활성
										// 배열에 현재점을 저장하고 카운트 증가
				m_ptData[m_nCount] = point;
				m_nCount++;
				// 체크변수 초기화 -> 다시 다각형을 그리기 위해
				m_bFirst = TRUE;
				m_bBezierDraw = true;
				ReleaseCapture();
				::ClipCursor(NULL);
				Invalidate(TRUE);
			}
		}
	}

	CView::OnRButtonDown(nFlags, point);
}


void CChap6PWGView::OnLineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK)
		m_colorPen = dlgColor.GetColor();
	Invalidate(true);
}


void CChap6PWGView::OnFaceColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor;
	if (dlgColor.DoModal() == IDOK)
		m_colorBrush = dlgColor.GetColor();
	Invalidate(true);
}



