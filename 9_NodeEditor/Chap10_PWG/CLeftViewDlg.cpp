// CLeftViewDlg.cpp: 구현 파일
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
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5View


IMPLEMENT_DYNCREATE(CLeftViewDlg, CFormView)



BEGIN_MESSAGE_MAP(CLeftViewDlg, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CLeftViewDlg::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CLeftViewDlg::OnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CLeftViewDlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_CHECK_EXPAND, &CLeftViewDlg::OnClickedCheckExpand)
END_MESSAGE_MAP()


// CMFCApplication5View 생성/소멸


CLeftViewDlg::CLeftViewDlg() noexcept
	: CFormView(IDD_FORMVIEW)
	// TODO: 여기에 생성 코드를 추가합니다.
{

}


CLeftViewDlg::~CLeftViewDlg()
{

}


void CLeftViewDlg::DoDataExchange(CDataExchange* pDX)
{

	DDX_Text(pDX, IDC_EDIT_NODE_TEXT, m_strNodeText);
	DDX_Text(pDX, IDC_EDIT_SELECTED_NODE, m_strSelectedNode);

	CFormView::DoDataExchange(pDX);
}


BOOL CLeftViewDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}


void CLeftViewDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_strSelectedNode = _T("루트 노드");

	((CButton*)GetDlgItem(IDC_CHECK_EXPAND))->SetCheck(TRUE);

	m_bChecked = true;
	UpdateData(FALSE);
}


// CMFCApplication5View 진단


#ifdef _DEBUG

void CLeftViewDlg::AssertValid() const
{
	CFormView::AssertValid();
}


void CLeftViewDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


CChap10PWGDoc* CLeftViewDlg::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap10PWGDoc)));
	return (CChap10PWGDoc*)m_pDocument;
}

#endif //_DEBUG


// CLeftViewDlg 메시지 처리기


void CLeftViewDlg::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CChap10PWGView *pView = (CChap10PWGView*)this->GetNextWindow();
	
	// 에러처리 - 입력할 텍스트가 비어있는지 검사	
		if (!m_strNodeText.IsEmpty()) {
			pView->GetTreeCtrl().InsertItem(m_strNodeText, pView->m_hSelectedNode, TVI_LAST);
			pView->GetTreeCtrl().Expand(pView->m_hSelectedNode, TVE_EXPAND);
		}
		else
			AfxMessageBox(_T("입력 노드의 텍스트를 입력하세요."));
	m_strNodeText.Empty();
	UpdateData(FALSE);
}


void CLeftViewDlg::OnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CChap10PWGView *pView = (CChap10PWGView*)this->GetNextWindow();

	// 입력할 텍스트가 비어 있는지 검사
	if (!m_strNodeText.IsEmpty()) {
		if (pView->m_hSelectedNode != pView->m_hRoot) {
			// 선택된 아이템의 텍스트를 수정한다.
			pView->GetTreeCtrl().SetItemText(pView->m_hSelectedNode, m_strNodeText);
			// 현재 선택된 아이템의 이름을 표현하는 Edit Control의 내용도 수정해준다.
			m_strSelectedNode = m_strNodeText;
		}
		else
			AfxMessageBox(_T("루트 노드는 수정해서는 안 됩니다."));
	}
	else
		AfxMessageBox(_T("수정 노드의 텍스트를 입력하세요."));

	m_strNodeText.Empty();

	UpdateData(FALSE);
}


void CLeftViewDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CChap10PWGView *pView = (CChap10PWGView*)this->GetNextWindow();

	if (pView->m_hSelectedNode != pView->m_hRoot) {
		if (MessageBox(_T("정말 삭제하시겠습니까?"), _T("삭제 경고"), MB_YESNO) == IDYES)
			pView->GetTreeCtrl().DeleteItem(pView->m_hSelectedNode);
	}
	else
		AfxMessageBox(_T("루트 노드는 삭제해서는 안 됩니다."));
}


void CLeftViewDlg::OnClickedCheckExpand()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CChap10PWGView *pView = (CChap10PWGView*)this->GetNextWindow();

	m_bChecked = !m_bChecked;
	pView->GetTreeCtrl().Expand(pView->m_hRoot, TVE_TOGGLE);
	pView->m_hSelectedNode = pView->m_hRoot;
	m_strSelectedNode = _T("루트 노드");
	UpdateData(FALSE);
}
