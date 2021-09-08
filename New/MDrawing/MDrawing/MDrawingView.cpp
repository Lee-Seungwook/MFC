
// MDrawingView.cpp: CMDrawingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MDrawing.h"
#endif

#include "MDrawingDoc.h"
#include "MDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMDrawingView

IMPLEMENT_DYNCREATE(CMDrawingView, CView)

BEGIN_MESSAGE_MAP(CMDrawingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMDrawingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMDrawingView 생성/소멸

CMDrawingView::CMDrawingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMDrawingView::~CMDrawingView()
{
}

BOOL CMDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMDrawingView 그리기

void CMDrawingView::OnDraw(CDC* pDC)
{
	CMDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	RECT rect;
	rect.left = m_ptX - 30;
	rect.top = m_ptY - 30;
	rect.bottom = m_ptY + 50;
	rect.right = m_ptX + 50;
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(&rect);

	pDC->TextOutW(20, 20, _T("다중 문서 인터페이스"));

}


// CMDrawingView 인쇄


void CMDrawingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMDrawingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMDrawingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMDrawingView 진단

#ifdef _DEBUG
void CMDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CMDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDrawingDoc* CMDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDrawingDoc)));
	return (CMDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CMDrawingView 메시지 처리기


void CMDrawingView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMDrawingDoc* pDoc = GetDocument();

	m_ptX = pDoc->m_ptX;
	m_ptY = pDoc->m_ptY;
}
