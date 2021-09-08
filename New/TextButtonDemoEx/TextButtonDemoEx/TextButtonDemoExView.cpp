
// TextButtonDemoExView.cpp: CTextButtonDemoExView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "TextButtonDemoEx.h"
#endif

#include "TextButtonDemoExDoc.h"
#include "TextButtonDemoExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextButtonDemoExView

IMPLEMENT_DYNCREATE(CTextButtonDemoExView, CView)

BEGIN_MESSAGE_MAP(CTextButtonDemoExView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTextButtonDemoExView 생성/소멸

CTextButtonDemoExView::CTextButtonDemoExView() noexcept :draw(FALSE), startPoint(0), endPoint(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_BtnRect = CRect(10, 10, 210, 40);
	m_BtnRect2 = CRect(10, 60, 210, 90);

	m_bClicked = FALSE;
	m_bClicked2 = FALSE;
}

CTextButtonDemoExView::~CTextButtonDemoExView()
{
}

BOOL CTextButtonDemoExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTextButtonDemoExView 그리기

void CTextButtonDemoExView::OnDraw(CDC* /*pDC*/)
{
	CTextButtonDemoExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTextButtonDemoExView 인쇄

BOOL CTextButtonDemoExView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTextButtonDemoExView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTextButtonDemoExView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTextButtonDemoExView 진단

#ifdef _DEBUG
void CTextButtonDemoExView::AssertValid() const
{
	CView::AssertValid();
}

void CTextButtonDemoExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextButtonDemoExDoc* CTextButtonDemoExView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextButtonDemoExDoc)));
	return (CTextButtonDemoExDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextButtonDemoExView 메시지 처리기

void CTextButtonDemoExView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (m_BtnRect.PtInRect(point)) {
	//	// 플래그를 토글하고 윈도우를 다시 그린다.
	//	m_bClicked = !m_bClicked;
	//	RedrawWindow(&m_BtnRect);
	//}

	//if (m_BtnRect2.PtInRect(point)) {
	//	// 플래그를 토글하고 윈도우를 다시 그린다.
	//	m_bClicked2 = !m_bClicked2;
	//	RedrawWindow(&m_BtnRect2);
	//}

	// 드래그 사각형
	draw = TRUE;

	startPoint = endPoint = point;
	CView::OnLButtonDown(nFlags, point);
}

void CTextButtonDemoExView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (draw) {
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);



		dc.Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

		endPoint = point;

		dc.Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	}
	CView::OnMouseMove(nFlags, point);
}

void CTextButtonDemoExView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (m_bClicked) {
	//	//플래그를 토글하고 윈도우를 다시 그린다.
	//	m_bClicked = !m_bClicked;
	//	RedrawWindow(&m_BtnRect);
	//}

	//if (m_bClicked2) {
	//	//플래그를 토글하고 윈도우를 다시 그린다.
	//	m_bClicked2 = !m_bClicked2;
	//	RedrawWindow(&m_BtnRect2);
	//}

	//if (m_BtnRect.PtInRect(point)) {
	//	AfxMessageBox(L"버튼을 클릭했습니다.");
	//}

	//if (m_BtnRect2.PtInRect(point)) {
	//	AfxMessageBox(L"버튼을 클릭했습니다.");
	//}

	draw = FALSE;

	CClientDC dc(this);

	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_COPYPEN);

	//
			//선지정


	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 0, 0);

	CPen NewPen;
	CPen* pOldPen = dc.SelectObject(&NewPen);

	CBrush NewBrush(RGB(0, 255, 255));//청색 브러시를 선택하여 삼각형을 칠한다.
	CBrush* pOldBrush = dc.SelectObject(&NewBrush);

	//색지정



	//

	CRect Rect(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	dc.Rectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	dc.DrawText(TEXT("테스트 진행 중입니다요"), &Rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_WORDBREAK);
	list.AddTail(CRect(startPoint, endPoint));


	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
	//기본값으로 재설정한다.
	CView::OnLButtonUp(nFlags, point);
}


void CTextButtonDemoExView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	
	//CRect Rect(20, 120, 500, 240);
	//CFont Font;
	//CFont *pOldFont;
	//LOGFONT lf;
	//::ZeroMemory(&lf, sizeof(lf));
	//lf.lfHeight = 36;
	//lf.lfItalic = TRUE;
	//lf.lfUnderline = TRUE;
	//lf.lfWeight = 700;
	//wsprintf(lf.lfFaceName, TEXT("%S"), TEXT("Arial"));
	//Font.CreateFontIndirect(&lf);
	//pOldFont = dc.SelectObject(&Font);

	//dc.TextOut(20, 20, _T("\t이것은 실습을 위한 \n문자열입니다."));

	//int nTabStop = 40;
	//dc.TabbedTextOut(20, 70, _T("\t이것은 실습을 위한 \n문자열입니다."), 1, &nTabStop, 20);

	//dc.SelectObject(pOldFont);

	//dc.SetTextColor(RGB(192, 0, 0));
	////대상 사각형에 문자열을 그린다.
	//dc.DrawText(TEXT("\t이것은 실습을 위한 \n문자열입니다."), &Rect, DT_VCENTER);
	//dc.SelectObject(pOldFont);

	// 버튼
	//CRect Rect(m_BtnRect);
	//CRect Rect2(m_BtnRect2);
	//Rect += CRect(1, 1, 1, 1);
	//Rect2 += CRect(1, 1, 1, 1);

	//dc.Rectangle(&Rect);
	//dc.FillSolidRect(&m_BtnRect, ::GetSysColor(COLOR_BTNFACE));

	//dc.Rectangle(&Rect2);
	//dc.FillSolidRect(&m_BtnRect2, ::GetSysColor(COLOR_BTNFACE));

	//if (m_bClicked) { // 눌려진 상태
	//	dc.Draw3dRect(m_BtnRect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));
	//	dc.Draw3dRect(m_BtnRect2, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));
	//	
	//}
	//else { // 평상시 상태
	//	dc.Draw3dRect(m_BtnRect, ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));
	//	dc.Draw3dRect(m_BtnRect2, ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));
	//	
	//}

	//if (m_bClicked2) { // 눌려진 상태
	//	dc.Draw3dRect(m_BtnRect2, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));

	//}
	//else { // 평상시 상태
	//	dc.Draw3dRect(m_BtnRect2, ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));

	//}

	//// 시스템이 정하는 버튼 관련 색상으로 텍스트를 그린다.
	//dc.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	//dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));

	//if (m_bClicked) {
	//	CRect Rect = m_BtnRect;
	//	
	//	// 눌려진 상태면 글씨가 출력되는 위치를 1픽셀 조절
	//	Rect += CRect(0, 0, 2, 2);
	//	
	//	dc.DrawText(L"Select", &Rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	//	
	//}
	//else if (m_bClicked2) {
	//	
	//	CRect Rect2 = m_BtnRect2;
	//	// 눌려진 상태면 글씨가 출력되는 위치를 1픽셀 조절
	//	
	//	Rect2 += CRect(0, 2, 2, 2);
	//	dc.DrawText(L"Select", &Rect2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	//	
	//}
	//else {
	//	dc.DrawText(L"OK", &m_BtnRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	//	dc.DrawText(L"System Info", &m_BtnRect2, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	//}


	// 드래그 사각형
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_COPYPEN);

	POSITION pos = list.GetHeadPosition();

	CRect rect;
	while (pos != NULL) { // 지워졌을경우 다시 그리기 위한 코드
		//
		//선지정
		LOGBRUSH lb;
		lb.lbStyle = BS_SOLID;
		lb.lbColor = RGB(0, 0, 0);

		CPen NewPen;
		CPen* pOldPen = dc.SelectObject(&NewPen);

		CBrush NewBrush(RGB(250, 250, 250));//청색 브러시를 선택하여 삼각형을 칠한다.
		CBrush* pOldBrush = dc.SelectObject(&NewBrush);

		//색지정
		//
		rect = list.GetNext(pos);

		dc.Rectangle(&rect);
		dc.DrawText(TEXT("테스트 진행 중입니다."), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_WORDBREAK);


		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
		//기본값으로 재설정한다.

	}
}






