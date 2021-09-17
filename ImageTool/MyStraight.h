#pragma once
#include <afx.h>
class CMyStraight :
	public CObject
{
	DECLARE_SERIAL(CMyStraight)
public:
	COLORREF m_PenColor;
	int m_nWidth; // ���� ���� 
	COLORREF m_ColorFill; // ������ ���� ä��� 
	int m_nStyle; // �� ��Ÿ��
	CArray<CPoint, CPoint&> m_ptArray;
public:
	CMyStraight();
	virtual ~CMyStraight();
	CMyStraight(COLORREF PenColor, int PenWidth, int Style);
	void ClickColor(COLORREF ColorFill);
	void Serialize(CArchive& ar);
	void Draw(CDC *pDC);
};

