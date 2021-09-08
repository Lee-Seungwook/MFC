
// ImgOutDemoView.cpp: CImgOutDemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImgOutDemo.h"
#endif

#include "ImgOutDemoDoc.h"
#include "ImgOutDemoView.h"
#include <atlimage.h> // CImage 클래스를 사용하기 위해 인클루드

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgOutDemoView

IMPLEMENT_DYNCREATE(CImgOutDemoView, CView)

BEGIN_MESSAGE_MAP(CImgOutDemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CImgOutDemoView 생성/소멸

CImgOutDemoView::CImgOutDemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImgOutDemoView::~CImgOutDemoView()
{
}

BOOL CImgOutDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImgOutDemoView 그리기

void CImgOutDemoView::OnDraw(CDC* /*pDC*/)
{
	CImgOutDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CImgOutDemoView 인쇄

BOOL CImgOutDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImgOutDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImgOutDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImgOutDemoView 진단

#ifdef _DEBUG
void CImgOutDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CImgOutDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgOutDemoDoc* CImgOutDemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgOutDemoDoc)));
	return (CImgOutDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgOutDemoView 메시지 처리기


void CImgOutDemoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	//// 로드할 이미지 파일의 경로
	//CString strImagePath = _T("test.png");
	//// 이미지 파일을 로드
	//CImage Image;
	//HRESULT hResult = Image.Load(strImagePath);
	//if (FAILED(hResult)) {
	//	CString strtmp = _T("ERROR: Failed to load");
	//	strtmp += strImagePath + _T("\n");
	//	TRACE(strtmp);
	//	return;
	//}  

	CImage Image;
	// 비트맵 리소스를 로드하여 출력
	Image.LoadFromResource(AfxGetInstanceHandle(), IDB_Image_Test);

	// 비트맵 이미지에 대한 DC를 생성
	CDC* pDC = CDC::FromHandle(Image.GetDC());
	// 이 이미지 DC에 문자열을 출력한다.
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(10, 30, TEXT("라이언"));
	Image.ReleaseDC();
	Image.BitBlt(dc.m_hDC, 10, 0);
	// 화면 DC에 문자열을 출력한다.
	/*dc.SetBkMode(TRANSPARENT);
	dc.TextOut(200, 30, TEXT("CIMAGE sample"));
*/
	// 화면 DC에 출력
	Image.BitBlt(dc.m_hDC, 0, 0);
}
