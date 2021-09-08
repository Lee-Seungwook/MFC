
// TriangleDemoExView.cpp: CTriangleDemoExView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TriangleDemoEx.h"
#endif

#include "TriangleDemoExDoc.h"
#include "TriangleDemoExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTriangleDemoExView

IMPLEMENT_DYNCREATE(CTriangleDemoExView, CView)

BEGIN_MESSAGE_MAP(CTriangleDemoExView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTriangleDemoExView 생성/소멸

CTriangleDemoExView::CTriangleDemoExView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTriangleDemoExView::~CTriangleDemoExView()
{
}

BOOL CTriangleDemoExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTriangleDemoExView 그리기

void CTriangleDemoExView::OnDraw(CDC* /*pDC*/)
{
	CTriangleDemoExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTriangleDemoExView 인쇄

BOOL CTriangleDemoExView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTriangleDemoExView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTriangleDemoExView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTriangleDemoExView 진단

#ifdef _DEBUG
void CTriangleDemoExView::AssertValid() const
{
	CView::AssertValid();
}

void CTriangleDemoExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTriangleDemoExDoc* CTriangleDemoExView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTriangleDemoExDoc)));
	return (CTriangleDemoExDoc*)m_pDocument;
}
#endif //_DEBUG


// CTriangleDemoExView 메시지 처리기


void CTriangleDemoExView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	DWORD style[] = { 6, 3 };
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(255, 0, 0);

	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_ROUND, 20, &lb);
	CPen *pOldPen = dc.SelectObject(&NewPen);

	CBrush NewBrush(RGB(192, 192, 192));
	CBrush *pOldBrush = dc.SelectObject(&NewBrush);

	dc.BeginPath();
		dc.MoveTo(120, 120);
		dc.LineTo(240, 120);
		
		dc.LineTo(240, 240);
		dc.LineTo(120, 240);
		
		dc.LineTo(120, 120);
	dc.EndPath();
	dc.StrokeAndFillPath();
}
