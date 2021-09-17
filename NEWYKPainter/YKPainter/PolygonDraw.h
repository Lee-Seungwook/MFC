#pragma once
#include "drawobject.h"

class PolygonDraw :
	public DrawObject
{
private:
	CList<CPoint, CPoint> m_points;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;
	FIGURETYPE m_type;

public:
	PolygonDraw(void);
	virtual ~PolygonDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);
	void addPoint(CPoint& point);
	void setProps(FIGURETYPE& type, int& Thickness, COLORREF& lineColor, COLORREF& fillColor);
};
