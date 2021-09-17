#include "StdAfx.h"
#include "PolygonDraw.h"

PolygonDraw::PolygonDraw(void)
{
}

PolygonDraw::~PolygonDraw(void)
{
	m_points.RemoveAll();
}

void PolygonDraw::draw(CDC* pDc) {
	int size = m_points.GetSize();
	CPoint *points = new CPoint[size];
	POSITION pos = m_points.GetHeadPosition();

	for (int i=0; i<size; i++) {
		points[i] = m_points.GetNext(pos);
	}
	
	if (m_type == BORDERONLY) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);

		CPen *oldPen = pDc->SelectObject(&pen);
		CGdiObject* oldBrush = pDc->SelectStockObject(NULL_BRUSH);

		pDc->Polygon(points, size);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
	} else if (m_type == BORDERFILL) {
		CPen pen(PS_SOLID, m_Thickness, m_lineColor);
		CBrush brush(m_fillColor);

		CPen* oldPen = pDc->SelectObject(&pen);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Polygon(points, size);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
	} else if (m_type == NOBORDERFILL) {
		CBrush brush(m_fillColor);

		CGdiObject* oldPen = pDc->SelectStockObject(NULL_PEN);
		CBrush* oldBrush = pDc->SelectObject(&brush);

		pDc->Polygon(points, size);

		pDc->SelectObject(oldBrush);
		pDc->SelectObject(oldPen);
	}
}

int PolygonDraw::drawType(void) {
	return POLYGON;
}

void PolygonDraw::addPoint(CPoint& point)
{
	m_points.AddTail(point);
}

void PolygonDraw::setProps(FIGURETYPE& type, int& Thickness, COLORREF& lineColor, COLORREF& fillColor) {
	m_type = type;
	m_Thickness = Thickness;
	m_lineColor = lineColor;
	m_fillColor = fillColor;
}

void PolygonDraw::serialize(CArchive& ar) {
	int type = (int)m_type;

	ar << drawType() << type << m_Thickness << m_lineColor << m_fillColor << m_points.GetSize();

	POSITION pos = m_points.GetHeadPosition();
	while (pos != NULL) {
		ar << m_points.GetNext(pos);
	}
}

void PolygonDraw::deserialize(CArchive& ar) {
	int size;
	CPoint point;
	int type;

	ar >> type >> m_Thickness >> m_lineColor >> m_fillColor >> size;
	
	m_type = (FIGURETYPE)type;

	for (int i=0; i<size; i++) {
		ar >> point;
		addPoint(point);
	}
}