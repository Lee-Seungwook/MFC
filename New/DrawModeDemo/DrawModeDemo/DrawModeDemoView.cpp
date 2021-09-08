
// DrawModeDemoView.cpp: CDrawModeDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DrawModeDemo.h"
#endif

#include "DrawModeDemoDoc.h"
#include "DrawModeDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawModeDemoView

IMPLEMENT_DYNCREATE(CDrawModeDemoView, CView)

BEGIN_MESSAGE_MAP(CDrawModeDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
//ON_WM_DRAWCLIPBOARD()
//ON_WM_DRAWITEM()
ON_WM_PAINT()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CDrawModeDemoView 생성/소멸

CDrawModeDemoView::CDrawModeDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptBegin = CPoint(0, 0);
	m_ptEnd = CPoint(0, 0);

	m_ptDragBegin = CPoint(0, 0);
	m_ptDragEnd = CPoint(0, 0);
}

CDrawModeDemoView::~CDrawModeDemoView()
{
}

BOOL CDrawModeDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDrawModeDemoView 그리기

void CDrawModeDemoView::OnDraw(CDC* /*pDC*/)
{
	CDrawModeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CDrawModeDemoView 인쇄

BOOL CDrawModeDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CDrawModeDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CDrawModeDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CDrawModeDemoView 진단

#ifdef _DEBUG
void CDrawModeDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawModeDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawModeDemoDoc* CDrawModeDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawModeDemoDoc)));
	return (CDrawModeDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawModeDemoView 메시지 처리기


//void CDrawModeDemoView::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnMButtonDown(nFlags, point);
//}


void CDrawModeDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//  마우스를 캡쳐하고 드래그가 시작됨
	SetCapture();
	//최초 드래그 시작시에는 시작/끝 좌표를 같은 값으로 설정
	m_ptDragBegin = point;
	m_ptDragEnd = point;
	CView::OnLButtonDown(nFlags, point);
}


void CDrawModeDemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 드래그가 끝났으면 붉은 실선의 시작/ 끝 좌표를 설정하고
	// 윈도우를 다시 그린다.
	if (GetCapture() == this)
	{
		m_ptBegin = m_ptDragBegin;
		m_ptEnd = m_ptDragEnd;
		RedrawWindow();
	}


	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CDrawModeDemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 마우스가 캡쳐된 상태(드래그)면 반전된 실선을 그린다.
	if (GetCapture() == this)
	{
		DrawInvertLine(point);
	}
	CView::OnMouseMove(nFlags, point);
}

void CDrawModeDemoView::DrawInvertLine(CPoint point) {
	CClientDC dc(this);
	//두께가 40인 펜을 생성한다.
	CPen NewPen(PS_SOLID, 40, RGB(0, 128, 0));
	CPen* pOldPen = (CPen*)dc.SelectObject(&NewPen);
	//그리기 모드를 반전모드로 변경한다.
	dc.SetROP2(R2_NOT);

	//기존에 반전된 선이 그려진 좌표에 한번 더 반전된 선을 그린다.
	//따라서 반전된 이미지가 원래대로 복원된다.
	dc.MoveTo(m_ptDragBegin);
	dc.LineTo(m_ptDragEnd);

	m_ptDragEnd = point;

	//새 좌표로 반전된 선을 그려서 이미지를 반전시킨다.
	dc.MoveTo(m_ptDragBegin);
	dc.LineTo(m_ptDragEnd);

	dc.SelectObject(pOldPen);
}





void CDrawModeDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//배경 이미지를 로드하여 출력한다.
	CImage Image;
	Image.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP1);
	Image.BitBlt(dc.m_hDC, 0, 0);

	//그려야 할 실선의 시작/끝 좌표가 같으면 그리지 않는다.
	if (m_ptBegin == m_ptEnd)	return;

	CPen NewPen(PS_SOLID, 40, RGB(192, 0, 0));
	CPen* pOldPen = (CPen*)dc.SelectObject(&NewPen);

	dc.MoveTo(m_ptBegin);
	dc.LineTo(m_ptEnd); // 여기서 그렸던 선을 그린다.

	dc.SelectObject(pOldPen);
}


void CDrawModeDemoView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 바탕 화면 윈도우에 대한 포인터를 얻는다.
	CWnd * pWnd = GetDesktopWindow();
	CWindowDC dc(pWnd);
	CPen NewPen(PS_SOLID, 10, RGB(0, 0, 0));
	CPen * pOldPen = (CPen*)dc.SelectObject(&NewPen);

	int nPrebMode = dc.SetROP2(R2_NOTXORPEN);

	// 바탕화면 윈도우에 그리기를 수행
	for (int i = 0; i < 300; i += 3) {
		dc.Rectangle(20, 10, 210 + i, 210 + i);
		::Sleep(5);
		dc.Rectangle(20, 10, 210 + i, 210 + i);
	}

	dc.SelectObject(pOldPen);
	dc.SetROP2(nPrebMode);
	pWnd->RedrawWindow();


	CView::OnRButtonDown(nFlags, point);
} // p.306
