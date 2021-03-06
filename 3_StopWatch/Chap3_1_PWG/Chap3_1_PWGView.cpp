
// Chap3_1_PWGView.cpp: CChap31PWGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chap3_1_PWG.h"
#endif

#include "Chap3_1_PWGDoc.h"
#include "Chap3_1_PWGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap31PWGView

IMPLEMENT_DYNCREATE(CChap31PWGView, CView)

BEGIN_MESSAGE_MAP(CChap31PWGView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CChap31PWGView 생성/소멸

CChap31PWGView::CChap31PWGView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_strStopWatch = _T("00: 00. 00");
	m_nCount = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_nMSec = 0;
	m_bStopWatchRun = false; /// 모두 초기화 해줌(디폴트가 false가 아님)
}

CChap31PWGView::~CChap31PWGView()
{
}

BOOL CChap31PWGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CChap31PWGView 그리기

void CChap31PWGView::OnDraw(CDC* pDC)
{
	CChap31PWGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CFont big_font;
	big_font.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

	CRect rect;
	GetClientRect(&rect);
	CClientDC dc(this);
	dc.SelectObject(&big_font); /// 폰트 입히기
	dc.DrawText(m_strStopWatch, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	for (int i = 0; i < m_nCount; i++)
		pDC->TextOut(10, 10+(i*20), m_strRecord[i]); /// y축을 기준으로 20간격으로 순서대로 출력
}


// CChap31PWGView 인쇄

BOOL CChap31PWGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CChap31PWGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CChap31PWGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CChap31PWGView 진단

#ifdef _DEBUG
void CChap31PWGView::AssertValid() const
{
	CView::AssertValid();
}

void CChap31PWGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap31PWGDoc* CChap31PWGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap31PWGDoc)));
	return (CChap31PWGDoc*)m_pDocument;
}
#endif //_DEBUG


// CChap31PWGView 메시지 처리기


void CChap31PWGView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_nMSec++; /// SetTimer(0,10,NULL)이기 때문에 0.01초 당 OnTimer함수가 호출되므로 해당 초마다 후위증가연산 시킴
	if (m_nMSec == 100) {
		m_nSecond++;
		m_nMSec = 0;
	}
	if (m_nSecond == 60) {
		m_nMinute++;
		m_nSecond = 0;
	}

	m_strStopWatch.Format(_T("%02d: %02d. %02d"), m_nMinute, m_nSecond, m_nMSec);

	Invalidate();

	CView::OnTimer(nIDEvent);
}

void CChap31PWGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStopWatchRun) {
		KillTimer(0);
		m_bStopWatchRun = false;
	} /// 스톱워치가 작동중일 때, KillTimer로 작동 중지시키고 작동 중지라는 bool인 false를 넣어줌
	else {
		SetTimer(0, 10, NULL);
		m_bStopWatchRun = true;
	} /// 스톱워치가 중지상태일 때, SetTimer로 작동 시켜주고 작동중이라는 bool인 true를 넣어줌

	CView::OnLButtonDown(nFlags, point);
}


void CChap31PWGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStopWatchRun) {
		if (nChar == VK_SPACE) {
			if (m_nCount == 40) {
				m_strRecord->Empty();
				m_nCount = 0;
				AfxMessageBox(_T("기록이 초기화 됩니다."), MB_ICONWARNING);
			} /// 40을 초과하면 더이상 기록이 불가능하므로 초기화 시켜줌
			m_strRecord[m_nCount].Format(m_strStopWatch); /// 해당 CString배열에 각각의 기록을 SPACE마다 작동시켜줌
			m_nCount++; /// 횟수를 늘려줌
		}
	}
	else {
		AfxMessageBox(_T("중지 상태에서는 기록이 불가능합니다."), MB_ICONWARNING);
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChap31PWGView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStopWatchRun) {
		AfxMessageBox(_T("작동 중에는 스톱워치를 초기화시킬 수 없습니다."), MB_ICONWARNING);
	}
	else {
		if (m_strStopWatch == _T("00: 00. 00")) {
			AfxMessageBox(_T("이미 초기화된 상태입니다."), MB_ICONWARNING);
		} /// 이미 초기환된 상태인데 또 초기화하려 달려들때
		else if (AfxMessageBox(_T("스톱워치를 초기화하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
			m_strStopWatch.Format(_T("00: 00. 00"));
			m_nCount = 0;
		} /// m_strStopWatch에 사용 흔적이 남아있을때, 우클릭하면 초키화 시켜줌
	}
	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}


void CChap31PWGView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_bStopWatchRun) {
		KillTimer(0);
	} // 종료할 때 KillTimer해줌
}
