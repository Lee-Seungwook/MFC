#include "pch.h"
#include "MyStraight.h"

IMPLEMENT_SERIAL(CMyStraight, CObject, 1)

CMyStraight::CMyStraight(void)
{
	m_PenColor = RGB(0, 0, 0);
	m_nStyle = 0;
	m_nWidth = 5;
	m_ColorFill = RGB(0, 0, 0);
}

CMyStraight::~CMyStraight(void)
{

}

CMyStraight::CMyStraight(COLORREF PenColor, int PenWidth, int Style)
{
	m_PenColor = PenColor;
	m_nWidth = PenWidth;
	m_nStyle = Style;
}

void CMyStraight::ClickColor(COLORREF ColorFill)
{
	m_ColorFill = ColorFill;
}

void CMyStraight::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring()) {
		ar << m_PenColor << m_nWidth << m_nStyle;
		m_ptArray.Serialize(ar);
	}
	else {
		ar >> m_PenColor >> m_nWidth >> m_nStyle;
		m_ptArray.Serialize(ar);
	}
}

void CMyStraight::Draw(CDC *pDC)
{
	LOGBRUSH lbr;
	lbr.lbStyle = BS_SOLID;
	lbr.lbColor = m_PenColor;
	lbr.lbHatch = 0;

	CPen pen(PS_GEOMETRIC | m_nStyle, m_nWidth, &lbr, 0, 0);// »ö°ú ±¼±â
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_ptArray[0]);
	for (int i = 0; i < m_ptArray.GetSize(); i++)
	{
		
		pDC->LineTo(m_ptArray[i]);
	}
	pDC->SelectObject(pOldPen);
}
