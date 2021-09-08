
// SaveGrayDemoView.cpp: CSaveGrayDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SaveGrayDemo.h"
#endif

#include "SaveGrayDemoDoc.h"
#include "SaveGrayDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSaveGrayDemoView

IMPLEMENT_DYNCREATE(CSaveGrayDemoView, CView)

BEGIN_MESSAGE_MAP(CSaveGrayDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSaveGrayDemoView 생성/소멸

CSaveGrayDemoView::CSaveGrayDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSaveGrayDemoView::~CSaveGrayDemoView()
{
}

BOOL CSaveGrayDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSaveGrayDemoView 그리기

void CSaveGrayDemoView::OnDraw(CDC* /*pDC*/)
{
	CSaveGrayDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSaveGrayDemoView 인쇄

BOOL CSaveGrayDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSaveGrayDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSaveGrayDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSaveGrayDemoView 진단

#ifdef _DEBUG
void CSaveGrayDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CSaveGrayDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSaveGrayDemoDoc* CSaveGrayDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaveGrayDemoDoc)));
	return (CSaveGrayDemoDoc*)m_pDocument;
}
#endif //_DEBUG

inline void RGBtoGray(COLORREF& rgb) {
	BYTE byGray = (GetRValue(rgb) * 30 + GetGValue(rgb) * 59 + GetBValue(rgb) * 11) / 100;

	rgb = RGB(byGray, byGray, byGray);
}

// CSaveGrayDemoView 메시지 처리기



void CSaveGrayDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 바탕 화면 윈도우 객체에 대한 포인터를 얻음
	CWnd* pWndDesktop = GetDesktopWindow();
	CWindowDC ScrDC(pWndDesktop); // 바탕 화면 윈도우 DC
	CWindowDC dc(this); // 뷰 윈도우 DC

	// 바탕 화면 크기 및 색상수와 동일한 비트맵 이미지를 만듬
	CImage Image;
	Image.Create(300, 300, ScrDC.GetDeviceCaps(BITSPIXEL));

	// 이미지 DC와 화면 DC에 바탕 화면 윈도우 DC를 출력
	CDC* pDC = CDC::FromHandle(Image.GetDC());
	pDC->BitBlt(0, 0, 300, 300, &ScrDC, 0, 0, SRCCOPY);
	Image.ReleaseDC();

	// 일부 (200 * 200)를 흑백 이미지로 변환 // 흑백변환 코드로 활용
	COLORREF rgb;
	for (int x = 0; x < 200; x++) { // 폭
		for (int y = 0; y < 200; ++y) { // 높이
			rgb = Image.GetPixel(x, y);
			//Gray RGB 값으로 변환
			RGBtoGray(rgb);
			Image.SetPixel(x, y, rgb); // 39, 149행 활용할것
		}
	}

	// 흑백으로 변환된 이미지를 환면 DC에 출력
	Image.BitBlt(dc.m_hDC, 0, 0);
	CView::OnLButtonDown(nFlags, point);
}


void CSaveGrayDemoView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 바탕 화면 윈도우 객체에 대한 포인터를 얻음
	CWnd* pWndDesktop = GetDesktopWindow();
	CWindowDC ScrDC(pWndDesktop); // 바탕 화면 위동우 Dc
	CClientDC dc(this);

	// 바탕 화면 윈도우의 크기를 알아낸다.
	CRect Rect;
	pWndDesktop->GetWindowRect(&Rect);

	//바탕 화면 크기 및 색상 수와 동일한 비트맵 이미지를 만든다.
	CImage Image;
	int cx = Rect.Width(); // 바탕 화면 폭
	int cy = Rect.Height(); // 바탕 화면 높이
	Image.Create(cx, cy, ScrDC.GetDeviceCaps(BITSPIXEL));

	// 이미지 DC와 화면 DC에 바탕 화면 윈도우 화면을 출력
	CDC *pDC = CDC::FromHandle(Image.GetDC());
	pDC->BitBlt(0, 0, cx, cy, &ScrDC, 0, 0, SRCCOPY);
	dc.BitBlt(0, 0, cx, cy, pDC, 0, 0, SRCCOPY);
	Image.ReleaseDC();

	//JPEG 형시으로 바탕 화면 이미지를 저장
	Image.Save(TEXT("DESKTOP.jpg"), Gdiplus::ImageFormatJPEG);
	//저장된 이미지를 뷰어를 실행하여 보여준다.
	::ShellExecute(NULL, TEXT("open"), TEXT("Desktop.jpg"), NULL, NULL, SW_SHOW);

	CView::OnRButtonDown(nFlags, point); // p.281
}
