#pragma once
#include "drawobject.h"

class PencilDraw :
	public DrawObject
{
private:
	CList<CPoint, CPoint> m_points;
	int m_Thickness;
	COLORREF m_color;

public:
	PencilDraw(void);
	virtual ~PencilDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void addPoint(CPoint& point);
	void setPencil(int nWidth, COLORREF rgbColor);
};
