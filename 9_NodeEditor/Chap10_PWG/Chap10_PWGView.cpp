
// Chap10_PWGView.cpp: CChap10PWGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Chap10_PWG.h"
#endif

#include "Chap10_PWGDoc.h"
#include "Chap10_PWGView.h"
#include "CLeftViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChap10PWGView

IMPLEMENT_DYNCREATE(CChap10PWGView, CTreeView)

BEGIN_MESSAGE_MAP(CChap10PWGView, CTreeView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CChap10PWGView::OnTvnSelchanged)
END_MESSAGE_MAP()

// CChap10PWGView 생성/소멸

CChap10PWGView::CChap10PWGView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
}

CChap10PWGView::~CChap10PWGView()
{
}

BOOL CChap10PWGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CTreeView::PreCreateWindow(cs);
}


void CChap10PWGView::OnDraw(CDC* /*pDC*/)
{
	CChap10PWGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


void CChap10PWGView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_hRoot = GetTreeCtrl().InsertItem(_T("루트 노드"), TVI_ROOT, TVI_LAST);
	GetTreeCtrl().SelectItem(m_hRoot); // 첫 셀렉트를 아예 처음 루트 노드로 선택시켜놓음
	GetTreeCtrl().ModifyStyle(1, TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS);
}


// CChap10PWGView 인쇄

BOOL CChap10PWGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CChap10PWGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CChap10PWGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CChap10PWGView 진단

#ifdef _DEBUG
void CChap10PWGView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CChap10PWGView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CChap10PWGDoc* CChap10PWGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap10PWGDoc)));
	return (CChap10PWGDoc*)m_pDocument;
}
#endif //_DEBUG


// CChap10PWGView 메시지 처리기


void CChap10PWGView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CLeftViewDlg *pDlg = (CLeftViewDlg*)this->GetNextWindow(GW_HWNDPREV);

	// 현재 선택한 아이템의 핸들 값을 멤버 변수에 저장한다.
	m_hSelectedNode = pNMTreeView->itemNew.hItem;

	// 선택한 아이템의 이름을 선택된 노드에 뜨게 만든다.
	pDlg->m_strSelectedNode = GetTreeCtrl().GetItemText(m_hSelectedNode);
	pDlg->UpdateData(FALSE);

	*pResult = 0;
}
