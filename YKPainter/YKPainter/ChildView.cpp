// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "YKPainter.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "ToolValues.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
int i=0;
#endif

IMPLEMENT_DYNCREATE(CYKPainterView, CScrollView)

BEGIN_MESSAGE_MAP(CYKPainterView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)

	ON_COMMAND(ID_FILE_NEW, &CYKPainterView::OnFileNew)
	ON_COMMAND(ID_VIEW_ZOOMIN, &CYKPainterView::OnZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &CYKPainterView::OnZoomOut)
	ON_COMMAND(ID_VIEW_ZOOMDEFAULT, &CYKPainterView::OnViewZoomdefault)

	ON_COMMAND(ID_PENCIL, &CYKPainterView::OnPencil)
	ON_COMMAND(ID_FILL, &CYKPainterView::OnFill)
	ON_COMMAND(ID_BEELINE, &CYKPainterView::OnBeeLine)
	ON_COMMAND(ID_ELLIPSE, &CYKPainterView::OnEllipse)
	ON_COMMAND(ID_RECTANGLE, &CYKPainterView::OnRectangle)
	ON_COMMAND(ID_POLYGON, &CYKPainterView::OnPolygon)
	ON_COMMAND(ID_FONT, &CYKPainterView::OnFont)

	ON_UPDATE_COMMAND_UI(ID_PENCIL, &CYKPainterView::OnUpdatePencil)
	ON_UPDATE_COMMAND_UI(ID_FILL, &CYKPainterView::OnUpdateFill)
	ON_UPDATE_COMMAND_UI(ID_BEELINE, &CYKPainterView::OnUpdateBeeLine)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CYKPainterView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CYKPainterView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_POLYGON, &CYKPainterView::OnUpdatePolygon)
	ON_UPDATE_COMMAND_UI(ID_FONT, &CYKPainterView::OnUpdateFont)

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

CYKPainterView::CYKPainterView() {
	_bDrawMode = FALSE;
	_bDoing = FALSE;
	_nZoomRate = 100;
	_memDc = NULL;
	_bitmap = NULL;
	_oldRadius = 0;
	
	_rect.left = _rect.top = 0;
	_rect.bottom = 600;
	_rect.right = 800;
}

CYKPainterView::~CYKPainterView() {}

// CChildView 메시지 처리기

BOOL CYKPainterView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.x = _rect.top;
	cs.y = _rect.left;
	cs.cx = _rect.bottom;
	cs.cy = _rect.right;
	
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return CWnd::PreCreateWindow(cs);
}

void CYKPainterView::setStatusBar() {
	CString str;

	switch (GetDocument()->CurDrawType) {
		case DEFAULT:
			str.Format("선택된 도구 없음");
			break;
		case PENCIL:
			str = "펜 그리기 도구";
			break;
		case FILL:
			str = "채우기 도구";
			break;
		case BEELINE:
			str = "직선 그리기 도구";
			break;
		case CIRCLE:
			str = "원 그리기 도구";
			break;
		case RECTANGLE:
			str = "사각형 그리기 도구";
			break;
		case POLYGON:
			str = "다각형 그리기 도구";
			break;
		case TEXT:
			str = "텍스트 도구";
			break;
	}
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, str);
}

void CYKPainterView::OnPencil() {
	if (GetDocument()->CurDrawType == PENCIL) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = PENCIL;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}

void CYKPainterView::OnUpdatePencil(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == PENCIL); 
}

void CYKPainterView::OnFill() { 
	if (GetDocument()->CurDrawType == FILL) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = FILL;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);

}
void CYKPainterView::OnUpdateFill(CCmdUI* pCmdUI) { 
	pCmdUI->SetCheck(GetDocument()->CurDrawType == FILL); 
}

void CYKPainterView::OnBeeLine() { 
	if (GetDocument()->CurDrawType == BEELINE) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = BEELINE;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CYKPainterView::OnUpdateBeeLine(CCmdUI* pCmdUI) { 
	pCmdUI->SetCheck(GetDocument()->CurDrawType == BEELINE); 
}

void CYKPainterView::OnEllipse() { 
	TRACE("OnEllipse");
	if (GetDocument()->CurDrawType == CIRCLE) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = CIRCLE;
	}
	setStatusBar();
	
	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CYKPainterView::OnUpdateEllipse(CCmdUI* pCmdUI) { 
	pCmdUI->SetCheck(GetDocument()->CurDrawType == CIRCLE); 
}

void CYKPainterView::OnRectangle() {
	if (GetDocument()->CurDrawType == RECTANGLE) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = RECTANGLE;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}
void CYKPainterView::OnUpdateRectangle(CCmdUI* pCmdUI) { 
	pCmdUI->SetCheck(GetDocument()->CurDrawType == RECTANGLE); 
}

void CYKPainterView::OnPolygon() { 
	if (GetDocument()->CurDrawType == POLYGON) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = POLYGON;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}

void CYKPainterView::OnUpdatePolygon(CCmdUI* pCmdUI) { 
	pCmdUI->SetCheck(GetDocument()->CurDrawType == POLYGON); 
}

void CYKPainterView::OnFont() {
	if (GetDocument()->CurDrawType == TEXT) {
		GetDocument()->CurDrawType = DEFAULT;
	} else {
		GetDocument()->CurDrawType = TEXT;
	}
	setStatusBar();

	AfxGetMainWnd()->SendMessage(WM_TOOBAR_NOTIFY, GetDocument()->CurDrawType);
}

void CYKPainterView::OnUpdateFont(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(GetDocument()->CurDrawType == TEXT); 
}

void CYKPainterView::OnZoomIn() {
	_nZoomRate += 50;
	Invalidate(FALSE);
}

void CYKPainterView::OnViewZoomdefault() {
	TRACE("OnViewZoomdefault\n");
	_nZoomRate = 100;
	Invalidate(TRUE);
}

void CYKPainterView::OnZoomOut() {
	_nZoomRate -= 50;
//	_oldBitmap = _memDc->SelectObject(_bitmap);
//	CBrush blue_brush(RGB(0, 0, 255));
//	CBrush *p_old_brush = _memDc->SelectObject(&blue_brush);
//	_memDc->Rectangle(100, 100, 400, 400);
	Invalidate(TRUE);
}


BOOL CYKPainterView::OnPreparePrinting(CPrintInfo* pInfo) {
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CYKPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CYKPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CYKPainterView::OnFileNew() {
	GetDocument()->OnNewDocument();
	Invalidate(TRUE);
}

void CYKPainterView::OnSize(UINT nType, int cx, int cy)
{
	TRACE("Onsize\n");
	CView::OnSize(nType, cx, cy);

	CSize sizeTotal(_rect.right, _rect.bottom);
	CSize sizePage(cx - 50, cy - 50);
	CSize sizeLine(50, 50);

	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
	Invalidate(TRUE);
}

void CYKPainterView::OnInitialUpdate() {
//	GetClientRect(_rect);
	_memDc = new CDC();
	_bitmap = new CBitmap();
	
	_memDc->CreateCompatibleDC(GetDC());
	_bitmap->CreateCompatibleBitmap(GetDC(), _rect.Width(), _rect.Height());
	
	_oldBitmap = _memDc->SelectObject(_bitmap);
}

void CYKPainterView::OnDestroy() {
	_bitmap->DeleteObject();
	_memDc->DeleteDC();	

	CView::OnDestroy();
}


void CYKPainterView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {

	CView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(_nZoomRate, _nZoomRate);
	pDC->SetWindowExt(100, 100);

	CGdiObject* old = pDC->SelectStockObject(GRAY_BRUSH);
	CRect rect;
	pDC->GetClipBox(&rect);
	pDC->PatBlt(_rect.right, rect.top, rect.Width() - _rect.Width(), rect.Height(), PATCOPY);
	pDC->PatBlt(rect.left, _rect.bottom, _rect.Width(), rect.Height() - _rect.Height(), PATCOPY);
	pDC->SelectObject(old);
}


void CYKPainterView::OnDraw(CDC* pDc) {
	CRect rec, rect;
	GetClientRect(rec);
	
	TRACE("OnDraw Rect(%d, %d, %d, %d)\n", rec.top, rec.left, rec.bottom, rec.right);
	
	pDc->GetClipBox(&rect);
	TRACE("OnDraw ClipBox(%d, %d, %d, %d)\n", rect.top, rect.left, rect.bottom, rect.right);
	
	YKPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	_oldBitmap = _memDc->SelectObject(_bitmap);
	CGdiObject* old = _memDc->SelectStockObject(WHITE_BRUSH);
	CGdiObject* oldPen = _memDc->SelectStockObject(WHITE_PEN);
	_memDc->Rectangle(rec);
	_memDc->SelectObject(oldPen);

	CPtrList* list = &pDoc->getDrawObjects();

	POSITION pos = list->GetHeadPosition();
	while (pos != NULL) {
		((DrawObject*)list->GetNext(pos))->draw(_memDc);
	}
	

//	pDc->SetBkColor(RGB(255, 0, 0));

	pDc->BitBlt(0, 0, _rect.Width(), _rect.Height(), _memDc, 0, 0, SRCCOPY);

	_memDc->SelectObject(old);
	_memDc->SelectObject(_oldBitmap);
}

void CYKPainterView::OnLButtonDown(UINT nFlags, CPoint point) {
	TRACE("OnButtonDown : %d [%d, %d]\n", nFlags, point.x, point.y);
	_bDrawMode = TRUE;
	YKPainterDoc* doc = GetDocument();

	CClientDC dc(this);

	//다각형 그리는 중..
	if (doc->CurDrawType == POLYGON && _bDoing) {
		CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
		CPen *oldPen = dc.SelectObject(&cpen);

		dc.MoveTo(_drawTo);
		dc.LineTo(point);
		_oldPoint = point;

		dc.SelectObject(oldPen);
		return;
	}

	SetCapture();
	
	switch (doc->CurDrawType) {
		case PENCIL:
			doc->getPencilDraw(TRUE)->addPoint(point);
			doc->getPencilDraw()->setPencil(ToolValues::LineWidth, ToolValues::FgColor);
			break;
		case FILL:
			doc->getFillDraw(TRUE)->setPoint(point);
			doc->getFillDraw()->setColor(ToolValues::FgColor);			
			Invalidate(FALSE);
			break;
		case BEELINE:
			doc->getBeeLineDraw(TRUE);
			doc->getBeeLineDraw()->setBeeLine(ToolValues::LineWidth, ToolValues::FgColor);
			break;
		case RECTANGLE:
			doc->getRactangleDraw(TRUE);
			doc->getRactangleDraw()->setProps(ToolValues::FigureType, ToolValues::LineWidth, ToolValues::FgColor, ToolValues::BgColor);
			break;
		case CIRCLE:
			doc->getEllipseDraw(TRUE);
			doc->getEllipseDraw()->setProps(ToolValues::FigureType, ToolValues::LineWidth, ToolValues::FgColor, ToolValues::BgColor);
			break;
		case POLYGON:
			doc->getPolygonDraw(TRUE)->addPoint(point);
			doc->getPolygonDraw()->setProps(ToolValues::FigureType, ToolValues::LineWidth, ToolValues::FgColor, ToolValues::BgColor);
			break;
		case TEXT:
			doc->getTextDraw(TRUE)->setPosition(point);
			doc->getTextDraw()->setColor(ToolValues::FgColor, ToolValues::BgColor);
			doc->getTextDraw()->setFontName(ToolValues::FontName);
			doc->getTextDraw()->setFontMode(ToolValues::FontMode);
			doc->getTextDraw()->setFontSize(ToolValues::FontSize);

			TEXTMETRIC txtKey;
			dc.GetTextMetrics(&txtKey);
			CreateSolidCaret(1, txtKey.tmHeight);
			SetCaretPos(point);
			ShowCaret();

			break;
	}

	_anchor = _drawTo = _oldPoint = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CYKPainterView::OnMouseMove(UINT nFlags, CPoint point) {
	CString str;
	str.Format("마우스 좌표 (%4d, %4d)", point.x, point.y);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText(2, str);

	if (_bDrawMode) {
		int oldMode;
		int radius;

		YKPainterDoc* doc = GetDocument();
		CClientDC dc(this);

		CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
		CBrush cbrush(ToolValues::BgColor);
		CPen *oldPen = dc.SelectObject(&cpen);
		CBrush *oldBrush = dc.SelectObject(&cbrush);
		
		switch (doc->CurDrawType) {
			case PENCIL:
				dc.MoveTo(_anchor);
				dc.LineTo(point);
				_anchor = point;
				doc->getPencilDraw()->addPoint(point);
				break;

			case BEELINE:
				oldMode = dc.SetROP2(R2_NOT);

				dc.MoveTo(_anchor);
				dc.LineTo(_oldPoint);
				
				dc.MoveTo(_anchor);
				dc.LineTo(point);
				_oldPoint = point;
				
				dc.SetROP2(oldMode);
				break;

			case CIRCLE:
				oldMode = dc.SetROP2(R2_NOT);
				dc.SelectStockObject(NULL_BRUSH);

				radius = getOblique(_anchor, point);
				dc.Ellipse(_anchor.x - _oldRadius, _anchor.y - _oldRadius, _anchor.x + _oldRadius, _anchor.y + _oldRadius);
				dc.Ellipse(_anchor.x - radius, _anchor.y - radius, _anchor.x + radius, _anchor.y + radius);				
				
				dc.SetROP2(oldMode);
				_oldRadius = radius;
				break;

			case RECTANGLE:
				oldMode = dc.SetROP2(R2_NOT);
				dc.SelectStockObject(NULL_BRUSH);
				dc.Rectangle(_oldPoint.x, _oldPoint.y, _anchor.x, _anchor.y);
				dc.Rectangle(_anchor.x, _anchor.y, point.x, point.y);
				_oldPoint = point;
				dc.SetROP2(oldMode);
				break;

			case POLYGON:
				oldMode = dc.SetROP2(R2_NOT);
				dc.MoveTo(_drawTo);
				dc.LineTo(_oldPoint);
				dc.MoveTo(_drawTo);
				dc.LineTo(point);
				_oldPoint = point;
				dc.SetROP2(oldMode);
				break;
		}

		dc.SelectObject(oldPen);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CYKPainterView::OnLButtonUp(UINT nFlags, CPoint point) {
	TRACE("OnButtonUp : %d\n", nFlags);
	
	if (_bDrawMode) {
		_bDrawMode = FALSE;
		YKPainterDoc* doc = GetDocument();
		ASSERT_VALID(doc);
		
		if (doc->CurDrawType == POLYGON) {
			CClientDC dc(this);

			CPen cpen(PS_SOLID, ToolValues::LineWidth, ToolValues::FgColor);
			CPen *oldPen = dc.SelectObject(&cpen);
			
			dc.MoveTo(_drawTo);
			dc.LineTo(point);
			
			dc.SelectObject(oldPen);

			doc->getPolygonDraw()->addPoint(point);

			_drawTo = point;
			_bDoing = TRUE;
			return;
		}
		::ReleaseCapture();

		switch (doc->CurDrawType) {
			case BEELINE:
				doc->getBeeLineDraw()->setPoint(_anchor, point);
				break;
			case RECTANGLE:
				doc->getRactangleDraw()->setRect(_anchor, point);
				break;
			case CIRCLE:
				doc->getEllipseDraw()->setCircle(_anchor, _oldRadius);
				_oldRadius = 0;
				break;
		}

		Invalidate(FALSE);
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CYKPainterView::OnLButtonDblClk(UINT nFlags, CPoint point) {
	TRACE("OnButtonDblClk : %d\n", nFlags);
	_bDrawMode = FALSE;
	YKPainterDoc* doc = GetDocument();
	ASSERT_VALID(doc);

	
	if ((doc->CurDrawType == POLYGON) && _bDoing) {
		doc->getPolygonDraw()->addPoint(point);
		
		_bDoing = FALSE;
		Invalidate(FALSE);
	}
	::ReleaseCapture();

}

void CYKPainterView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	YKPainterDoc* doc = GetDocument();

	if (doc->CurDrawType == TEXT) {
		CClientDC dc(this);
		TextDraw* td = doc->getTextDraw();
		
		CSize strSize;

		if (nChar == 8) {	//백스페이스
			td->subtractChar();
		} else {
			td->insertChar(nChar);
		}
		
		CFont font;
		font.CreatePointFont(ToolValues::FontSize, ToolValues::FontName);
		/*if (ToolValues::LogFont.lfCharSet != 0) {
			font.CreateFontIndirect(&(ToolValues::LogFont));
		}*/
		CFont* oldFont = dc.SelectObject(&font);

		strSize = dc.GetTextExtent(td->getString());

		SetCaretPos(CPoint(_anchor.x + strSize.cx, _anchor.y));
		ShowCaret();

		dc.SelectObject(oldFont);

		Invalidate(TRUE);
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CYKPainterView::OnEraseBkgnd(CDC* pDC) {	
	return FALSE;
}

BOOL CYKPainterView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	switch (GetDocument()->CurDrawType) {
		case PENCIL:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_PENCIL));
			break;
		case FILL:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_FILL));
			break;
		case BEELINE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_BEELINE));
			break;
		case CIRCLE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_CIRCLE));
			break;
		case RECTANGLE:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_RECT));
			break;
		case POLYGON:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_POLY));
			break;
		case TEXT:
			::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_TEXT));
			break;
		default:
			CView::OnSetCursor(pWnd, nHitTest, message);
			break;
	}

	return TRUE;
}

void CYKPainterView::OnSetFocus(CWnd* pOldWnd)
{
//	TRACE("OnSetFocus\n");
	CView::OnSetFocus(pOldWnd);

//	YKPainterDoc* doc = GetDocument();
//
//	if (doc->CurDrawType == TEXT) {
//		CClientDC dc(this);
//
//		TEXTMETRIC txtKey;
//		dc.GetTextMetrics(&txtKey);
//		CreateSolidCaret(1, txtKey.tmHeight);
//
//		CFont font;
//		font.CreatePointFont(ToolValues::FontSize, ToolValues::FontName);
//		/*if (ToolValues::LogFont.lfCharSet != 0) {
//			font.CreateFontIndirect(&(ToolValues::LogFont));
//		}*/
//		CFont* oldFont = dc.SelectObject(&font);
//		
//		CSize strSize = dc.GetTextExtent(doc->getTextDraw()->getString());
//
////		SetCaretPos(CPoint(_anchor.x + strSize.cx, _anchor.y));
//		ShowCaret();
//	}
}

void CYKPainterView::OnKillFocus(CWnd* pNewWnd) {
//	TRACE("OnKillFocus\n");
	CView::OnKillFocus(pNewWnd);
	
	HideCaret();
	::DestroyCaret();
}

#ifdef _DEBUG
void CYKPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CYKPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

YKPainterDoc* CYKPainterView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(YKPainterDoc)));
	return (YKPainterDoc*)m_pDocument;
}
#endif //_DEBUG

int CYKPainterView::getOblique(CPoint& p1, CPoint& p2)
{
	int x, y;

	x = abs(p1.x - p2.x);
	y = abs(p1.y - p2.y);

	return (int)sqrt((double)x * x + y * y);
}

void CYKPainterView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACE("OnVScroll(%d, %d)\n", nSBCode, nPos);

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CYKPainterView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TRACE("OnHScroll(%d, %d)\n", nSBCode, nPos);

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}
