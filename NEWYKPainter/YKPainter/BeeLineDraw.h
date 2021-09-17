#pragma once
#include "drawobject.h"

class BeeLineDraw :
	public DrawObject
{
private:
	CPoint m_start;
	CPoint m_end;

	int m_lineThickness;
	COLORREF m_color;

public:
	BeeLineDraw(void);
	virtual ~BeeLineDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void setPoint(CPoint& start, CPoint& end);
	void setBeeLine(int& lineWidth, COLORREF& color);
};
