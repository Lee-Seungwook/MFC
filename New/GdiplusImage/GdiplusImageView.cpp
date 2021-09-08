
// GdiplusImageView.cpp: CGdiplusImageView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GdiplusImage.h"
#endif

#include "GdiplusImageDoc.h"
#include "GdiplusImageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusImageView

IMPLEMENT_DYNCREATE(CGdiplusImageView, CView)

BEGIN_MESSAGE_MAP(CGdiplusImageView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CGdiplusImageView 생성/소멸

CGdiplusImageView::CGdiplusImageView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGdiplusImageView::~CGdiplusImageView()
{
}

BOOL CGdiplusImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGdiplusImageView 그리기

void CGdiplusImageView::OnDraw(CDC* /*pDC*/)
{
	CGdiplusImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGdiplusImageView 인쇄

BOOL CGdiplusImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGdiplusImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGdiplusImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGdiplusImageView 진단

#ifdef _DEBUG
void CGdiplusImageView::AssertValid() const
{
	CView::AssertValid();
}

void CGdiplusImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGdiplusImageDoc* CGdiplusImageView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGdiplusImageDoc)));
	return (CGdiplusImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CGdiplusImageView 메시지 처리기


void CGdiplusImageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	//// jpg 이미지 출력
	//Image img(_T("res\\사진.jpg")); // 이미지 클래스 선언 및 이미지 불러오기
	//// graphics.DrawImage(&img, 0, 0);  // 이미지 화면에 출력
	//// graphics.DrawImage(&img, 100, 50, img.GetWidth() / 4, img.GetHeight() / 4);

	//Point points[] = { Point(200, 0), Point(img.GetWidth(), 0), Point(0, img.GetHeight()) }; // 좌표를 지정하여 기울어진 이미지를 그림
	//graphics.DrawImage(&img, points, 3); // 세 개의 좌표이기 때문에 맨 뒤의 3이 들어감

	// 비트맵 파일
	Bitmap bmp(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	CachedBitmap cachedbmp(&bmp, &graphics);

	graphics.DrawImage(&bmp, 10, 10);
	graphics.DrawCachedBitmap(&cachedbmp, bmp.GetWidth() + 20, 10);
}
