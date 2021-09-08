
// PenBrushDemoView.cpp: CPenBrushDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PenBrushDemo.h"
#endif

#include "PenBrushDemoDoc.h"
#include "PenBrushDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPenBrushDemoView

IMPLEMENT_DYNCREATE(CPenBrushDemoView, CView)

BEGIN_MESSAGE_MAP(CPenBrushDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPenBrushDemoView 생성/소멸

CPenBrushDemoView::CPenBrushDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPenBrushDemoView::~CPenBrushDemoView()
{
}

BOOL CPenBrushDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPenBrushDemoView 그리기

void CPenBrushDemoView::OnDraw(CDC* /*pDC*/)
{
	CPenBrushDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPenBrushDemoView 인쇄

BOOL CPenBrushDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPenBrushDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPenBrushDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPenBrushDemoView 진단

#ifdef _DEBUG
void CPenBrushDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPenBrushDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPenBrushDemoDoc* CPenBrushDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPenBrushDemoDoc)));
	return (CPenBrushDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CPenBrushDemoView 메시지 처리기


void CPenBrushDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//CPen NewPen(PS_SOLID, 20, RGB(192, 192, 192));
	//CPen *pOldPen = dc.SelectObject(&NewPen);

	//dc.MoveTo(40, 40);
	//dc.LineTo(240, 40);
	//dc.SelectObject(pOldPen);

	//dc.MoveTo(40, 40);
	//dc.LineTo(240, 40);

	/*LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(192, 192, 192);

	CPen arNewPen[3];
	CPen* pOldPen = NULL;
	arNewPen[0].CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_ROUND, 20, &lb);
	arNewPen[1].CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE, 20, &lb);
	arNewPen[2].CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, 20, &lb);

	for (int i = 0; i < 3; i++) {
		pOldPen = dc.SelectObject(&arNewPen[i]);
		dc.MoveTo(40, 40 * (i + 1));
		dc.LineTo(240, 40 * (i + 1));
		dc.SelectObject(pOldPen);
		dc.MoveTo(40, 40 * (i + 1));
		dc.LineTo(240, 40 * (i + 1));

		arNewPen[i].DeleteObject();
	}*/

	/*DWORD style[] = { 6, 3 };
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(255, 0, 0);

	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC | PS_USERSTYLE | PS_ENDCAP_FLAT, 10, &lb, 2, style);
	CPen* pOldPen = dc.SelectObject(&NewPen);

	dc.MoveTo(40, 40);
	dc.LineTo(240, 40);

	dc.SelectObject(pOldPen);*/

	/*CBrush NewBrush(HS_CROSS, RGB(192, 0, 0));
	CBrush *pOldBrush = dc.SelectObject(&NewBrush);

	dc.Rectangle(20, 20, 140, 140);

	dc.SelectObject(pOldBrush);*/
	CBrush NewBrush;

	CBitmap Bmp;
	Bmp.LoadBitmapA(IDB_BITMAP1);
	NewBrush.CreatePatternBrush(&Bmp);
	CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	CRect Rect;
	GetClientRect(&Rect);
	dc.Rectangle(&Rect);

	dc.SelectObject(pOldBrush);
}
