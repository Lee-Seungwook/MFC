
// SDrawingView.cpp: CSDrawingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDrawing.h"
#endif

#include "SDrawingDoc.h"
#include "SDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDrawingView

IMPLEMENT_DYNCREATE(CSDrawingView, CView)

BEGIN_MESSAGE_MAP(CSDrawingView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSDrawingView 생성/소멸

CSDrawingView::CSDrawingView() noexcept
	: m_ptX(0)
	, m_ptY(0)
	, m_crColor(0)
	, m_reRect(100,100,300,300)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_crColor = BLACK_BRUSH;
}

CSDrawingView::~CSDrawingView()
{
}

BOOL CSDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDrawingView 그리기

void CSDrawingView::OnDraw(CDC* pDC)
{
	CSDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->TextOutW(150, 50, _T("Hello, MFC 2021"));
	pDC->SelectStockObject(m_crColor);
	pDC->Rectangle(m_reRect);
}

void CSDrawingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDrawingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSDrawingView 진단

#ifdef _DEBUG
void CSDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CSDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDrawingDoc* CSDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDrawingDoc)));
	return (CSDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDrawingView 메시지 처리기


void CSDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON) {
		CClientDC dc(this);

		dc.MoveTo(m_ptX, m_ptY);
		dc.LineTo(point.x, point.y);

		m_ptX = point.x;
		m_ptY = point.y;
	}

	CView::OnMouseMove(nFlags, point);
}


void CSDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptX = point.x;
	m_ptY = point.y;

	if (m_reRect.PtInRect(point)) {
		if (m_crColor == BLACK_BRUSH) {
			m_crColor = WHITE_BRUSH;
		}
		else if (m_crColor == GRAY_BRUSH) {
			m_crColor = BLACK_BRUSH;
		}
		else {
			m_crColor = GRAY_BRUSH;
		}
		InvalidateRect(m_reRect);
	}

	CView::OnLButtonDown(nFlags, point);
}
