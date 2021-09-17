#include "StdAfx.h"
#include "BeeLineDraw.h"

BeeLineDraw::BeeLineDraw(void) {}

BeeLineDraw::~BeeLineDraw(void) {}

void BeeLineDraw::draw(CDC* pDc) {
	CPen pen(PS_SOLID, m_lineThickness, m_color);
	CPen* oldPen = pDc->SelectObject(&pen);

	pDc->MoveTo(m_start);
	pDc->LineTo(m_end);

	pDc->SelectObject(oldPen);
}

int BeeLineDraw::drawType(void) {
	return BEELINE;
}
void BeeLineDraw::setPoint(CPoint& start, CPoint& end)
{
	m_start = start;
	m_end = end;
}

void BeeLineDraw::setBeeLine(int& lineThickness, COLORREF& color) {
	m_lineThickness = lineThickness;
	m_color = color;
}

void BeeLineDraw::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_start << m_end << m_lineThickness << m_color;
}

void BeeLineDraw::deserialize(CArchive& ar) {
	ar >> m_start >> m_end >> m_lineThickness >> m_color;
}