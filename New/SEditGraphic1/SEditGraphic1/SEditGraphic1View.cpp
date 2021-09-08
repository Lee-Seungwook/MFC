
// SEditGraphic1View.cpp: CSEditGraphic1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SEditGraphic1.h"
#endif

#include "SEditGraphic1Doc.h"
#include "SEditGraphic1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSEditGraphic1View

IMPLEMENT_DYNCREATE(CSEditGraphic1View, CView)

BEGIN_MESSAGE_MAP(CSEditGraphic1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSEditGraphic1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FIG_CIR, &CSEditGraphic1View::OnFigCir)
	ON_COMMAND(ID_FIG_RECT, &CSEditGraphic1View::OnFigRect)
	ON_COMMAND(ID_FIG_LINE, &CSEditGraphic1View::OnFigLine)
	ON_COMMAND(ID_FIG_CROSS, &CSEditGraphic1View::OnFigCross)
	ON_COMMAND(ID_FIG_APPLE, &CSEditGraphic1View::OnFigApple)
END_MESSAGE_MAP()

// CSEditGraphic1View 생성/소멸

CSEditGraphic1View::CSEditGraphic1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSEditGraphic1View::~CSEditGraphic1View()
{
}

BOOL CSEditGraphic1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSEditGraphic1View 그리기

void CSEditGraphic1View::OnDraw(CDC* pDC)
{
	CSEditGraphic1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CFont font, *p0ldFont;
	font.CreatePointFont(300, _T("BroadWay")); // 글자크기, 폰트 설정
	p0ldFont = (CFont*)pDC->SelectObject(&font);
	CString strInput1 = _T(" << Input Data >>");
	CString strInput2 = pDoc->GetText();
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOut(0, 20, strInput1);
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(pDoc->ColorGet());
	pDC->TextOut(50, 100, strInput2);

	switch (m_nOption) {
	case 1: {
		CBrush brush(RGB(0, 255, 0));
		// Brush object 선택
		CBrush *p0ldBrush = pDC->SelectObject(&brush); // Brush Object 선택
		pDC->Ellipse(200, 200, 400, 400);
		brush.DeleteObject();
		break;
	}

	case 2: {
		CBrush brush(RGB(150, 0, 150));
		// Brush Object 생성
		CBrush *p0ldBrush = pDC->SelectObject(&brush); // Brush Object 선택
		pDC->Rectangle(200, 200, 400, 400);
		brush.DeleteObject();
		break;
	}

	case 3: {
		CDC* pDC = GetDC();
		int nPenType[] = { PS_SOLID, PS_DOT, PS_DASHDOT, PS_DASH, PS_DASHDOTDOT };

		for (int i = 0; i < sizeof(nPenType) / sizeof(nPenType[0]); i++) {
			CPen pen(nPenType[i], 1, RGB(0, 0, 255));
			pDC->SelectObject(&pen);

			/*-----------직선-------------*/
			/*
			pDC->MoveTo(100, 200 + i * 50);
			pDC->LineTo(500, 200 + i * 50);

			/*-----------사선-------------*/
			
			pDC->MoveTo(100, 200 + i * 50);
			pDC->LineTo(500, 200 + i * 50);

			
		}
		break;
	}

	case 4: {
		CBrush brush(HS_DIAGCROSS, RGB(255, 90, 0));

		CBrush *p0ldBrush = pDC->SelectObject(&brush);
		pDC->RoundRect(200, 200, 400, 400, 50, 50);
		pDC->SelectObject(p0ldBrush);
		brush.DeleteObject();
		break;
	}

	case 5: {
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);
		CBrush brush(&bitmap);

		//Brush Object 선택
		CBrush *p0ldBrush = pDC->SelectObject(&brush); // Brush Object 선택

		pDC->SetBkColor(TRANSPARENT);

		pDC->RoundRect(300, 200, 400, 400, 50, 50);
		pDC->SelectObject(&brush);
		brush.DeleteObject(); //Brush Object제거

		break;
	}

		
	
	default:
		break;
	}
}


// CSEditGraphic1View 인쇄


void CSEditGraphic1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSEditGraphic1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSEditGraphic1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSEditGraphic1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSEditGraphic1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSEditGraphic1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSEditGraphic1View 진단

#ifdef _DEBUG
void CSEditGraphic1View::AssertValid() const
{
	CView::AssertValid();
}

void CSEditGraphic1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSEditGraphic1Doc* CSEditGraphic1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSEditGraphic1Doc)));
	return (CSEditGraphic1Doc*)m_pDocument;
}
#endif //_DEBUG


// CSEditGraphic1View 메시지 처리기


void CSEditGraphic1View::OnFigCir()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nOption = 1;
	Invalidate();
}


void CSEditGraphic1View::OnFigRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nOption = 2;
	Invalidate();
}


void CSEditGraphic1View::OnFigLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nOption = 3;
	Invalidate();
}


void CSEditGraphic1View::OnFigCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nOption = 4;
	Invalidate();
}


void CSEditGraphic1View::OnFigApple()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nOption = 5;
	Invalidate();
}
