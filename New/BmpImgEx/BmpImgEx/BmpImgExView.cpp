
// BmpImgExView.cpp: CBmpImgExView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BmpImgEx.h"
#endif

#include "BmpImgExDoc.h"
#include "BmpImgExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBmpImgExView

IMPLEMENT_DYNCREATE(CBmpImgExView, CView)

BEGIN_MESSAGE_MAP(CBmpImgExView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CBmpImgExView 생성/소멸

CBmpImgExView::CBmpImgExView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CBmpImgExView::~CBmpImgExView()
{
}

BOOL CBmpImgExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBmpImgExView 그리기

void CBmpImgExView::OnDraw(CDC* /*pDC*/)
{
	CBmpImgExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBmpImgExView 인쇄

BOOL CBmpImgExView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBmpImgExView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBmpImgExView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBmpImgExView 진단

#ifdef _DEBUG
void CBmpImgExView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpImgExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpImgExDoc* CBmpImgExView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpImgExDoc)));
	return (CBmpImgExDoc*)m_pDocument;
}
#endif //_DEBUG


// CBmpImgExView 메시지 처리기


void CBmpImgExView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	/*CDC MemDC;
	BITMAP bmpInfo;

	MemDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmap(IDB_Test_Img);

	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBmp);*/

	/*CImage Image;
	Image.LoadFromResource(AfxGetInstanceHandle(), IDB_Test_Img);

	CDC *pDC = CDC::FromHandle(Image.GetDC());
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(200, 30, TEXT("이승욱"));
	Image.ReleaseDC();
	Image.BitBlt(dc.m_hDC, 0, 0);*/

	//CDC MemDC;
	//BITMAP bmpInfo;
	//MemDC.CreateCompatibleDC(&dc);

	//CBitmap bmp;
	//CBitmap* pOldBmp = NULL;
	//bmp.LoadBitmap(IDB_Test_Img);

	//bmp.GetBitmap(&bmpInfo);
	//pOldBmp = MemDC.SelectObject(&bmp);

	//dc.StretchBlt(20, 20, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	//BLENDFUNCTION bf; // 투명 이미지 구조체
	//bf.BlendOp = AC_SRC_OVER; // default
	//bf.BlendFlags = 0; // default
	//bf.SourceConstantAlpha = 50; // 투명도
	//bf.AlphaFormat = 0; // 0 또는 default
	//// 반투명 이미지를 출력
	//dc.AlphaBlend(400, 20, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, bf);

	//MemDC.SelectObject(pOldBmp);

	CDC MemDC, MemDC2;
	BITMAP bmpInfo, bmpInfo2;
	MemDC.CreateCompatibleDC(&dc);
	MemDC2.CreateCompatibleDC(&dc);

	CBitmap bmp, bmp2;
	CBitmap* pOldBmp = NULL;
	CBitmap* pOldBmp2 = NULL;
	bmp.LoadBitmap(IDB_BITMAP1);
	bmp2.LoadBitmap(IDB_Test_Img);
	

	bmp.GetBitmap(&bmpInfo);
	bmp2.GetBitmap(&bmpInfo2);
	pOldBmp = MemDC.SelectObject(&bmp);
	pOldBmp2 = MemDC2.SelectObject(&bmp2);

	dc.StretchBlt(20, 20, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	dc.TransparentBlt(20, 100, bmpInfo2.bmWidth * 2, bmpInfo2.bmHeight * 2, &MemDC2, 0, 0, bmpInfo2.bmWidth, bmpInfo2.bmHeight, RGB(4, 4, 4));
}
