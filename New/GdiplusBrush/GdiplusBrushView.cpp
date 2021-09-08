
// GdiplusBrushView.cpp: CGdiplusBrushView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GdiplusBrush.h"
#endif

#include "GdiplusBrushDoc.h"
#include "GdiplusBrushView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusBrushView

IMPLEMENT_DYNCREATE(CGdiplusBrushView, CView)

BEGIN_MESSAGE_MAP(CGdiplusBrushView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusBrushView 생성/소멸

CGdiplusBrushView::CGdiplusBrushView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGdiplusBrushView::~CGdiplusBrushView()
{
}

BOOL CGdiplusBrushView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGdiplusBrushView 그리기

void CGdiplusBrushView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusBrushDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGdiplusBrushView 인쇄

BOOL CGdiplusBrushView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGdiplusBrushView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGdiplusBrushView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGdiplusBrushView 진단

#ifdef _DEBUG
void CGdiplusBrushView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusBrushView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusBrushDoc* CGdiplusBrushView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusBrushDoc)));
	return (CGdiplusBrushDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusBrushView 메시지 처리기


void CGdiplusBrushView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//// 파란색 브러쉬로 도형 칠하기
	//Graphics graphics(dc);
	//graphics.SetSmoothingMode(SmoothingModeHighQuality);

	//SolidBrush solidbrush(Color(255, 0, 0, 192));
	//graphics.FillRectangle(&solidbrush, 20, 20, 100, 100);
	//graphics.FillEllipse(&solidbrush, 150, 20, 100, 100);
	//graphics.FillEllipse(&solidbrush, 150, 20, 100, 100);
	//graphics.FillPie(&solidbrush, 300, 20, 100, 100, 180.0f, 90.0f);

	//// 그라데이션 브러쉬 생성
	//dc.TextOutW(25, 25, _T("GDI+ Gradient test string!")); // 텍스트 출력

	//Graphics graphics(dc);
	//graphics.SetSmoothingMode(SmoothingModeHighQuality); // 안티에일리어싱

	//// LinearGradientBrush lgBrush(Point(0, 0), Point(100, 100), Color(128, 221, 236, 255), Color(255, 86, 125, 204)); // 그라데이션 적용
	//// LinearGradientBrush lgBrush(Rect(10, 10, 200, 200), Color(128, 221, 236, 255), Color(255, 86, 125, 204), LinearGradientModeVertical); // 수평 그라데이션 적용
	//LinearGradientBrush lgBrush(Rect(10, 10, 200, 200), Color(128, 221, 236, 255), Color(255, 86, 125, 204), 45.0f, FALSE); // 45.0f는 각도


	//graphics.FillRectangle(&lgBrush, 0, 0, 600, 200); // 사각형 만들고 색 채우기

	// 이미지 
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);
	Image image(_T("res\\Texture.jpg"));
	TextureBrush txBrush(&image, WrapModeTile);

	CRect rectClient;
	GetClientRect(&rectClient);
	graphics.FillRectangle(&txBrush, 0, 0, rectClient.Width() / 2, rectClient.Height());

	txBrush.SetWrapMode(WrapModeTileFlipXY);
	graphics.FillRectangle(&txBrush, rectClient.Width() / 2, 0, rectClient.Width() / 2, rectClient.Height());
}
