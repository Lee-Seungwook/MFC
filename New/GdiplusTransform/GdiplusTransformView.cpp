
// GdiplusTransformView.cpp: CGdiplusTransformView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GdiplusTransform.h"
#endif

#include "GdiplusTransformDoc.h"
#include "GdiplusTransformView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusTransformView

IMPLEMENT_DYNCREATE(CGdiplusTransformView, CView)

BEGIN_MESSAGE_MAP(CGdiplusTransformView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGdiplusTransformView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusTransformView 생성/소멸

CGdiplusTransformView::CGdiplusTransformView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGdiplusTransformView::~CGdiplusTransformView()
{
}

BOOL CGdiplusTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGdiplusTransformView 그리기

void CGdiplusTransformView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGdiplusTransformView 인쇄


void CGdiplusTransformView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGdiplusTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGdiplusTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGdiplusTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGdiplusTransformView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGdiplusTransformView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGdiplusTransformView 진단

#ifdef _DEBUG
void CGdiplusTransformView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusTransformView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusTransformDoc* CGdiplusTransformView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusTransformDoc)));
	return (CGdiplusTransformDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusTransformView 메시지 처리기


void CGdiplusTransformView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	Pen pen(Color::Black, 3);
	Pen pen2(Color(255, 192, 0, 0), 3);
	Pen penLine(Color(255, 192, 0, 0), 2);
	penLine.SetDashStyle(DashStyleDot);

	graphics.DrawRectangle(&pen, Rect(30, 30, 150, 100));

	//Matrix transformMatrix;
	//transformMatrix.Translate(100.0f, 100.0f); // 0, 0을 다른 좌표로 재정의
	//transformMatrix.Rotate(45.0f); // 각도를 변환

	//graphics.SetTransform(&transformMatrix); // 변경사항 적용
	//graphics.DrawLine(&penLine, Point(-200, 0), Point(200, 0));
	//graphics.DrawLine(&penLine, Point(0, -200), Point(0, 200));
	//graphics.DrawRectangle(&pen2, Rect(30, 30, 150, 100));

	// matrix 사용하지 않고 적용
	graphics.TranslateTransform(100.0f, 100.0f);
	graphics.RotateTransform(45.0f);
	graphics.DrawLine(&penLine, Point(-200, 0), Point(200, 0));
	graphics.DrawLine(&penLine, Point(0, -200), Point(0, 200));
	graphics.DrawRectangle(&pen2, Rect(30, 30, 150, 100));
}
