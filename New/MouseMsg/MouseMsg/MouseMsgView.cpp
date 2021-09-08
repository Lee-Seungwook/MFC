
// MouseMsgView.cpp: CMouseMsgView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MouseMsg.h"
#endif

#include "MouseMsgDoc.h"
#include "MouseMsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseMsgView

IMPLEMENT_DYNCREATE(CMouseMsgView, CView)

BEGIN_MESSAGE_MAP(CMouseMsgView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()

// CMouseMsgView 생성/소멸

CMouseMsgView::CMouseMsgView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_ptMouse = CPoint(0, 0);
	m_ptLeft = CPoint(0, 0);
	m_ptRight = CPoint(0, 0);

}

CMouseMsgView::~CMouseMsgView()
{
}

BOOL CMouseMsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMouseMsgView 그리기

void CMouseMsgView::OnDraw(CDC* /*pDC*/)
{
	CMouseMsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMouseMsgView 인쇄

BOOL CMouseMsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMouseMsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMouseMsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMouseMsgView 진단

#ifdef _DEBUG
void CMouseMsgView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseMsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseMsgDoc* CMouseMsgView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseMsgDoc)));
	return (CMouseMsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseMsgView 메시지 처리기


void CMouseMsgView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CString strData = _T("");
	strData.Format(_T("X:%03d, Y:%03d"), m_ptMouse.x, m_ptMouse.y);
	dc.TextOut(10, 10, strData);

	strData.Format(_T("WM_LBUTTONDOWN X: % 03d, Y : % 03d"), m_ptLeft.x, m_ptLeft.y);
	dc.TextOut(10, 30, strData);

	strData.Format(_T("WM_RBUTTONDOWN X: % 03d, Y : % 03d"), m_ptRight.x, m_ptRight.y);
	dc.TextOut(10, 50, strData);
}


void CMouseMsgView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && (nFlags & MK_RBUTTON) == MK_RBUTTON) {
		m_ptMouse = point;
		RedrawWindow();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMouseMsgView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ptLeft = point;
	RedrawWindow();

	CView::OnLButtonDown(nFlags, point);
}


void CMouseMsgView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다. 
	m_ptRight = point;
	RedrawWindow();
	CView::OnRButtonDown(nFlags, point);
}


void CMouseMsgView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTmp = _T("");
	strTmp.Format(TEXT("OnMouseWheel() zDelta: %d\n"), zDelta);
	TRACE(strTmp);

	CView::OnMouseHWheel(nFlags, zDelta, pt);
}
