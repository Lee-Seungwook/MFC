#pragma once
#include "drawobject.h"

class FillDraw :
	public DrawObject
{
private:
	CPoint m_point;
	COLORREF m_color;

public:
	FillDraw(void);
	virtual ~FillDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setPoint(CPoint& point);
	void setColor(COLORREF& color);
};
