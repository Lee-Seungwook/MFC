#include "StdAfx.h"
#include "FillDraw.h"

FillDraw::FillDraw(void) {}

FillDraw::~FillDraw(void) {}

void FillDraw::draw(CDC* pDc) {
	CBrush brush(m_color);
	CBrush* oldBrush = pDc->SelectObject(&brush);

	pDc->ExtFloodFill(m_point.x, m_point.y, pDc->GetPixel(m_point), FLOODFILLSURFACE);
	pDc->SelectObject(oldBrush);
}

int FillDraw::drawType(void) {
	return FILL;
}

void FillDraw::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_point << m_color;
}

void FillDraw::deserialize(CArchive& ar) {
	ar >> m_point >> m_color;
}

void FillDraw::setPoint(CPoint& point)
{
	m_point = point;
}

void FillDraw::setColor(COLORREF& color) {
	m_color = color;
}