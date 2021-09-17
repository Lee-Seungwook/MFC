#pragma once
#include "drawobject.h"

class RectangleDraw :
	public DrawObject
{
private:
	CPoint m_topLeft, m_bottomRight;
	FIGURETYPE m_type;
	int m_Thickness;
	COLORREF m_lineColor;
	COLORREF m_fillColor;

public:
	RectangleDraw(void);
	virtual ~RectangleDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setRect(CPoint& topLeft, CPoint& bottomRight);
	void setProps(FIGURETYPE type, int& lineWidth, COLORREF& lineColor, COLORREF& fillColor);
};
