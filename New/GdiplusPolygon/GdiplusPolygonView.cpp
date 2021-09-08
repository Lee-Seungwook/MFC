
// GdiplusPolygonView.cpp: CGdiplusPolygonView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GdiplusPolygon.h"
#endif

#include "GdiplusPolygonDoc.h"
#include "GdiplusPolygonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusPolygonView

IMPLEMENT_DYNCREATE(CGdiplusPolygonView, CView)

BEGIN_MESSAGE_MAP(CGdiplusPolygonView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusPolygonView 생성/소멸

CGdiplusPolygonView::CGdiplusPolygonView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGdiplusPolygonView::~CGdiplusPolygonView()
{
}

BOOL CGdiplusPolygonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGdiplusPolygonView 그리기

void CGdiplusPolygonView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusPolygonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGdiplusPolygonView 인쇄

BOOL CGdiplusPolygonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGdiplusPolygonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGdiplusPolygonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGdiplusPolygonView 진단

#ifdef _DEBUG
void CGdiplusPolygonView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusPolygonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusPolygonDoc* CGdiplusPolygonView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusPolygonDoc)));
	return (CGdiplusPolygonDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusPolygonView 메시지 처리기


void CGdiplusPolygonView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	//// 사각형 그리기
	//Pen BlackPen(Color(255, 0, 0, 0), 20.0f);
	//graphics.DrawRectangle(&BlackPen, 30, 30, 100, 100); // 끝이 각진 사각형

	//BlackPen.SetLineJoin(LineJoinRound);
	//graphics.DrawRectangle(&BlackPen, 170, 30, 100, 100); // 끝이 둥근 사각형

	//// 원 그리기
	//Pen RedPen(Color(255, 192, 0, 0), 2.0f);
	//Pen GrayPen(Color(255, 192, 192, 192), 15.0f);

	//graphics.DrawEllipse(&GrayPen, 30, 30, 150, 150); // 원 그리기

	//graphics.DrawArc(&RedPen, 30, 30, 150, 150, 0.0f, 90.0f); // 원호
	//graphics.DrawPie(&RedPen, 30, 30, 150, 150, 180.0f, 90.0f); // 부채꼴

	// 다각형 그리기
	Pen RedPen(Color(255, 192, 0, 0), 2.0f);

	Point points[6] = { Point(30, 30), Point(180, 30), Point(180, 130), Point(130, 130), Point(130, 80), Point(30, 80) };
	graphics.DrawPolygon(&RedPen, points, 6);
}
