
// DCDrawingView.cpp: CDCDrawingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DCDrawing.h"
#endif

#include "DCDrawingDoc.h"
#include "DCDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCDrawingView

IMPLEMENT_DYNCREATE(CDCDrawingView, CView)

BEGIN_MESSAGE_MAP(CDCDrawingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDCDrawingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDCDrawingView 생성/소멸

CDCDrawingView::CDCDrawingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDCDrawingView::~CDCDrawingView()
{
}

BOOL CDCDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDCDrawingView 그리기

void CDCDrawingView::OnDraw(CDC* pDC)
{
	CDCDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	pDC->SelectObject(&pen);

	pDC->MoveTo(500, 0);
	pDC->LineTo(500, 1000);

	pDC->MoveTo(0, 300);
	pDC->LineTo(1000, 300);

	pen.DeleteObject();

	int sPenType = PS_SOLID;
	pen.CreatePen(sPenType, 2, RGB(255, 255, 255));
	pDC->SelectObject(&pen);
	

	CBrush brush(RGB(0, 255, 0));
	CBrush *p0ldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(100, 50, 400, 250);
	
	pDC->Rectangle(550, 50, 800, 250);
	
	pDC->Ellipse(100, 350, 400, 550);

	pDC->Rectangle(550, 350, 800, 550);




}


// CDCDrawingView 인쇄


void CDCDrawingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDCDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDCDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDCDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CDCDrawingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDCDrawingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDCDrawingView 진단

#ifdef _DEBUG
void CDCDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CDCDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDCDrawingDoc* CDCDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDCDrawingDoc)));
	return (CDCDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDCDrawingView 메시지 처리기
