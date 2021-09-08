
// GdiplusLineView.cpp: CGdiplusLineView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GdiplusLine.h"
#endif

#include "GdiplusLineDoc.h"
#include "GdiplusLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusLineView

IMPLEMENT_DYNCREATE(CGdiplusLineView, CView)

BEGIN_MESSAGE_MAP(CGdiplusLineView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusLineView 생성/소멸

CGdiplusLineView::CGdiplusLineView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGdiplusLineView::~CGdiplusLineView()
{
}

BOOL CGdiplusLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGdiplusLineView 그리기

void CGdiplusLineView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGdiplusLineView 인쇄

BOOL CGdiplusLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGdiplusLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGdiplusLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGdiplusLineView 진단

#ifdef _DEBUG
void CGdiplusLineView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusLineDoc* CGdiplusLineView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusLineDoc)));
	return (CGdiplusLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusLineView 메시지 처리기


void CGdiplusLineView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
						   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
						   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality); // 안티 에일리어싱 적용

	// 선 그리기
	/*Pen BluePen(Color(255, 0, 0, 255), 20.0f);
	Pen BlackPen(Color(128, 0, 0, 0), 20.0f);

	graphics.DrawLine(&BluePen, Point(10, 50), Point(210, 50));
	graphics.DrawLine(&BlackPen, Point(20, 60), Point(220, 60));*/

	// 꺽인 선 그리기( 선 이어서 그리기)
	//Pen BluePen(Color(255, 0, 0, 255), 20.0f);

	//Point point1(30, 10);
	//Point point2(30, 110);
	//Point point3(230, 20);
	//Point point4(230, 120);
	//Point points[4] = { point1, point2, point3, point4 };

	//BluePen.SetLineJoin(LineJoinRound);
	//// BluePen.SetDashStyle(DashStyleDot); // 굵은 점선
	//graphics.DrawLines(&BluePen, points, 4);
	
	//// 끝 부분 처리
	//Pen BluePen(Color(255, 0, 0, 255), 10.0f);
	//Point point1(30, 10);
	//Point point2(30, 110);
	//Point point3(230, 20);
	//Point point4(230, 120);
	//Point points[4] = { point1, point2, point3, point4 };

	//BluePen.SetLineJoin(LineJoinRound);
	//BluePen.SetStartCap(LineCapRoundAnchor); // 시작 부분 처리
	//BluePen.SetEndCap(LineCapArrowAnchor); // 끝 부분 처리
	//graphics.DrawLines(&BluePen, points, 4);

	// 곡선
	Pen RedPen(Color(255, 255, 0, 0), 2.0f);
	Pen GreenPen(Color(255, 0, 255, 0), 2.0f);
	Pen BluePen(Color(255, 0, 0, 255), 2.0f);

	Point points[6] = { Point(10, 150), Point(110, 10), Point(170, 250), Point(220, 120), Point(270, 150), Point(350, 150) };
	graphics.DrawCurve(&RedPen, points, 6, 0.0f); // 곡선 그리기, 끝의 인자가 클수록 휘는 정도가 더 커진다. (0.0f ~ 1.0f 사이의 값을 적용한다.)
	graphics.DrawCurve(&GreenPen, points, 6, 1.0f);
	graphics.DrawCurve(&BluePen, points, 6, 0.5f);
	

	
}
