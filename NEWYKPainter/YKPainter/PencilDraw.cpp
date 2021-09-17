#include "StdAfx.h"
#include "PencilDraw.h"

PencilDraw::PencilDraw(void) {
	m_Thickness = 1;
	m_color = RGB(0, 0, 0);
}

PencilDraw::~PencilDraw(void) {}

void PencilDraw::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_Thickness, m_color);
	CPen *oldPen = pDc->SelectObject(&pen);

	POSITION pos = m_points.GetHeadPosition();

	CPoint a = m_points.GetNext(pos);
	CPoint b;

	while (pos != NULL) {
		b = m_points.GetNext(pos);

		pDc->MoveTo(a);
		pDc->LineTo(b);
		a = b;
	}

	pDc->SelectObject(oldPen);
}
int PencilDraw::drawType(void) {
	return PENCIL;
}

void PencilDraw::serialize(CArchive& ar) {
	ar << drawType() << m_points.GetSize();

	POSITION pos = m_points.GetHeadPosition();
	while (pos != NULL) {
		ar << m_points.GetNext(pos);
	}
	
	ar << m_Thickness << m_color;
}

void PencilDraw::deserialize(CArchive& ar) {
	int size;
	CPoint point;

	ar >> size;
	
	for (int i=0; i<size; i++) {
		ar >> point;
		addPoint(point);
	}

	ar >> m_Thickness >> m_color;
}

void PencilDraw::addPoint(CPoint& point)
{
	m_points.AddTail(point);
}

void PencilDraw::setPencil(int nWidth, COLORREF rgbColor) {
	m_Thickness = nWidth;
	m_color = rgbColor;
}
