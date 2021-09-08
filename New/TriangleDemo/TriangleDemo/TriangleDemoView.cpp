
// TriangleDemoView.cpp: CTriangleDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TriangleDemo.h"
#endif

#include "TriangleDemoDoc.h"
#include "TriangleDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTriangleDemoView

IMPLEMENT_DYNCREATE(CTriangleDemoView, CView)

BEGIN_MESSAGE_MAP(CTriangleDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTriangleDemoView 생성/소멸

CTriangleDemoView::CTriangleDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTriangleDemoView::~CTriangleDemoView()
{
}

BOOL CTriangleDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTriangleDemoView 그리기

void CTriangleDemoView::OnDraw(CDC* /*pDC*/)
{
	CTriangleDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTriangleDemoView 인쇄

BOOL CTriangleDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTriangleDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTriangleDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTriangleDemoView 진단

#ifdef _DEBUG
void CTriangleDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTriangleDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTriangleDemoDoc* CTriangleDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTriangleDemoDoc)));
	return (CTriangleDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CTriangleDemoView 메시지 처리기


void CTriangleDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	

//	DWORD style[] = { 6, 3 };
//	LOGBRUSH lb;
//	lb.lbStyle = BS_SOLID;
//	lb.lbColor = RGB(192, 192, 192);
//
//	CPen NewPen;
//	NewPen.CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 20, &lb);
//	CPen *pOldPen = dc.SelectObject(&NewPen);
//
//	CBrush NewBrush(RGB(0, 0, 192));
//	CBrush* pOldBrush = dc.SelectObject(&NewBrush);
//
//	/*dc.BeginPath();
//		dc.MoveTo(190, 40);
//		dc.LineTo(290, 190);
//		dc.LineTo(90, 190);
//		dc.LineTo(190, 40);
//	dc.EndPath();
//	dc.StrokeAndFillPath();*/
//	 // 위와 밑의 코드 두 줄은 결과값이 동일하다. (삼각형)
//	/*POINT arPt[3] = { {190, 40}, {290, 190}, {90, 190} };
//	dc.Polygon(arPt, 3);
//*/
//	// 사각형
//	POINT arPt[4] = { {20, 20}, {140, 20}, {140, 140}, {20, 140} };
//	dc.Polygon(arPt, 4);
//
//	// 부채꼴 (반시계 방향으로 그린다.) // p.225
//	CRect PieRect(20, 160, 140, 280);
//	dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, PieRect.top), CPoint(PieRect.right, PieRect.CenterPoint().y));
//
//	PieRect = CRect(20, 300, 140, 460);
//	dc.Pie(PieRect, CPoint(PieRect.right, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, PieRect.top));
//
//	dc.SelectObject(pOldBrush);
//	dc.SelectObject(pOldPen);
//
	/*dc.MoveTo(190, 40);
	dc.LineTo(290, 190);
	dc.LineTo(90, 190);
	dc.LineTo(190, 40);*/

	DWORD style[] = { 8, 1 }; // 선 스타일{그려지는 범위, 그려지지 않는 범위}
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(192, 0, 0);

	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC | PS_USERSTYLE | PS_ENDCAP_FLAT | PS_JOIN_MITER, 3, &lb, 2, style);
	CPen *pOldPen = dc.SelectObject(&NewPen);

	CBrush NewBrush(RGB(192, 192, 192));
	CBrush *pOldBrush = dc.SelectObject(&NewBrush);
	
	dc.RoundRect(CRect(20, 20, 140, 140), CPoint(20, 20));

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
}
