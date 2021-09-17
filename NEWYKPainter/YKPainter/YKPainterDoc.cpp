// YKPainterDoc.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YKPainter.h"
#include "YKPainterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(YKPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(YKPainterDoc, CDocument)
END_MESSAGE_MAP()

YKPainterDoc::YKPainterDoc() {
	CurDrawType = DEFAULT;
	m_Cur = NULL;
}

YKPainterDoc::~YKPainterDoc() {}

BOOL YKPainterDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;

	DrawObject* obj;
	POSITION pos = m_DrawObjs.GetHeadPosition();
	while (pos != NULL) {
		obj = (DrawObject*)m_DrawObjs.GetNext(pos);
		delete obj;
	}
	m_DrawObjs.RemoveAll();

	return TRUE;
}

void YKPainterDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {		//저장
		POSITION pos = m_DrawObjs.GetHeadPosition();
		while (pos != NULL) {
			((DrawObject*)m_DrawObjs.GetNext(pos))->serialize(ar);
		}

	} else {	//로드
		int toolType;
		DrawObject *obj;

		do {
			ar >> toolType;

			switch (toolType) {
				case BEELINE:
					obj = new BeeLineDraw(); break;
				case PENCIL:
					obj = new PencilDraw(); break;
				case CIRCLE:
					obj = new EllipseDraw(); break;
				case POLYGON:
					obj = new PolygonDraw(); break;
				case RECTANGLE:
					obj = new RectangleDraw(); break;
				case FILL:
					obj = new FillDraw(); break;
				case TEXT:
					obj = new TextDraw(); break;
			}

			obj->deserialize(ar);
			m_DrawObjs.AddTail(obj);

		} while (!ar.IsBufferEmpty());
		
		((CFrameWnd*)AfxGetMainWnd())->GetActiveView()->Invalidate(TRUE);
	}
}

CPtrList& YKPainterDoc::getDrawObjects() {
	return m_DrawObjs;
}

TextDraw* YKPainterDoc::getTextDraw(BOOL bNew)
{
	if (bNew) {
		m_Cur = new TextDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (TextDraw*)m_Cur;
	} 
	if (m_Cur != NULL && m_Cur->drawType() == TEXT) {
		return (TextDraw*)m_Cur;
	}
	
	return NULL;
}

BeeLineDraw* YKPainterDoc::getBeeLineDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new BeeLineDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (BeeLineDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == BEELINE) {
		return (BeeLineDraw*)m_Cur;
	}
	return NULL;
}

FillDraw* YKPainterDoc::getFillDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new FillDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (FillDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == FILL) {	
		return (FillDraw*)m_Cur;
	}
	return NULL;
}

PencilDraw* YKPainterDoc::getPencilDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new PencilDraw();
		m_DrawObjs.AddTail(m_Cur);
		
		return (PencilDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == PENCIL) {	
		return (PencilDraw*)m_Cur;
	}
	return NULL;
}

EllipseDraw* YKPainterDoc::getEllipseDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new EllipseDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (EllipseDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == CIRCLE) {	
		return (EllipseDraw*)m_Cur;
	}
	return NULL;
}

RectangleDraw* YKPainterDoc::getRactangleDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new RectangleDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (RectangleDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == RECTANGLE) {
		return (RectangleDraw*)m_Cur;
	}
	return NULL;
}

PolygonDraw* YKPainterDoc::getPolygonDraw(bool bNew)
{
	if (bNew) {
		m_Cur = new PolygonDraw();
		m_DrawObjs.AddTail(m_Cur);

		return (PolygonDraw*)m_Cur;
	}
	if (m_Cur != NULL && m_Cur->drawType() == POLYGON) {	
		return (PolygonDraw*)m_Cur;
	}
	return NULL;
}

#ifdef _DEBUG
void YKPainterDoc::AssertValid() const {
	CDocument::AssertValid();
}

void YKPainterDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG