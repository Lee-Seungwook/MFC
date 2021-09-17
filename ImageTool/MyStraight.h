#pragma once
#include <afx.h>
class CMyStraight :
	public CObject
{
	DECLARE_SERIAL(CMyStraight)
public:
	COLORREF m_PenColor;
	int m_nWidth; // 선의 굵기 
	COLORREF m_ColorFill; // 눌러서 색상 채우기 
	int m_nStyle; // 선 스타일
	CArray<CPoint, CPoint&> m_ptArray;
public:
	CMyStraight();
	virtual ~CMyStraight();
	CMyStraight(COLORREF PenColor, int PenWidth, int Style);
	void ClickColor(COLORREF ColorFill);
	void Serialize(CArchive& ar);
	void Draw(CDC *pDC);
};

