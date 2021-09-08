
// BmpDisplayDemoView.cpp: CBmpDisplayDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BmpDisplayDemo.h"
#endif

#include "BmpDisplayDemoDoc.h"
#include "BmpDisplayDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBmpDisplayDemoView

IMPLEMENT_DYNCREATE(CBmpDisplayDemoView, CView)

BEGIN_MESSAGE_MAP(CBmpDisplayDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CBmpDisplayDemoView 생성/소멸

CBmpDisplayDemoView::CBmpDisplayDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CBmpDisplayDemoView::~CBmpDisplayDemoView()
{
}

BOOL CBmpDisplayDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBmpDisplayDemoView 그리기

void CBmpDisplayDemoView::OnDraw(CDC* /*pDC*/)
{
	CBmpDisplayDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBmpDisplayDemoView 인쇄

BOOL CBmpDisplayDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBmpDisplayDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBmpDisplayDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBmpDisplayDemoView 진단

#ifdef _DEBUG
void CBmpDisplayDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpDisplayDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpDisplayDemoDoc* CBmpDisplayDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpDisplayDemoDoc)));
	return (CBmpDisplayDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CBmpDisplayDemoView 메시지 처리기


void CBmpDisplayDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	//cdc memdc;
	//bitmap bmpinfo;

	//// 화면 dc와 호환되는 메모리 dc를 생성
	//memdc.createcompatibledc(&dc);
	//// 비트맵 리소스를 로딩한다.
	//cbitmap bmp;
	//cbitmap* poldbmp = null;
	//bmp.loadbitmap(idb_bitmap1);
	//// 로딩된 비트맵의 정보를 알아본다.
	//bmp.getbitmap(&bmpinfo);
	//// 메모리 dc에 선택한다.
	//poldbmp = memdc.selectobject(&bmp);
	//// 메모리 dc에 들어 있는 비트맵을 화면 dc로 복사하여 출력
	//dc.bitblt(0, 0, bmpinfo.bmwidth, bmpinfo.bmheight, &memdc, 0, 0, srccopy);
	//dc.stretchblt(300, 100, 256 * 2, 256 * 2, &memdc, 100, 180, 256, 256, srccopy);

	//dc.stretchblt(20, 20, bmpinfo.bmwidth * 2, bmpinfo.bmheight * 2, &memdc, 0, 0, bmpinfo.bmwidth, bmpinfo.bmheight, srccopy);
	//// 마지막 인자를 제외하면 stretchblt함수와 유사
	//dc.transparentblt(500, 100, bmpinfo.bmwidth * 2, bmpinfo.bmheight * 2, &memdc, 0, 0, bmpinfo.bmwidth, bmpinfo.bmheight, rgb(0, 0, 0)); // 투명 처리될 색상의 rgb 값
	//memdc.selectobject(poldbmp);

//	CDC MemDC;
//	BITMAP bmpInfo;
//	MemDC.CreateCompatibleDC(&dc);
//
//	CBitmap bmp;
//	CBitmap* pOldBmp = NULL;
//	bmp.LoadBitmap(IDB_Test_Image);
//
//	bmp.GetBitmap(&bmpInfo);
//	pOldBmp = MemDC.SelectObject(&bmp);
//
//	dc.StretchBlt(20, 20,
//		bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2,
//		&MemDC,
//		0, 0,
//		bmpInfo.bmWidth, bmpInfo.bmHeight,
//		SRCCOPY);			//래스터 연산 값.
//
////※ 마지막 인자를 제외하면 StretchBlt() 함수와 거의 동일. 
//
//	dc.TransparentBlt(250, 100,
//		bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2,
//		&MemDC,
//		0, 0,
//		bmpInfo.bmWidth, bmpInfo.bmHeight,
//		RGB(0, 255, 0));
//
//
//
//	MemDC.SelectObject(pOldBmp);

	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmap(IDB_Test_Image);

	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);

	dc.StretchBlt(20, 20, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	BLENDFUNCTION bf; // 투명 이미지 구조체
	bf.BlendOp = AC_SRC_OVER; // default
	bf.BlendFlags = 0; // default
	bf.SourceConstantAlpha = 50; // 투명도
	bf.AlphaFormat = 0; // 0 또는 default
	// 반투명 이미지를 출력
	dc.AlphaBlend(400, 20, bmpInfo.bmWidth * 2, bmpInfo.bmHeight * 2, &MemDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, bf);

	MemDC.SelectObject(pOldBmp);


}
