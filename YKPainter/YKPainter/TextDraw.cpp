#include "StdAfx.h"
#include "TextDraw.h"
#include "ToolValues.h"

TextDraw::TextDraw(void) {
	m_position.SetPoint(0, 0);
}

TextDraw::~TextDraw(void) {
}

void TextDraw::draw(CDC* pDc) {
	CFont font;
	
	font.CreatePointFont(m_fontSize, m_fontName);

	CFont* oldFont = pDc->SelectObject(&font);
	COLORREF oldColor = pDc->SetTextColor(m_fgColor);
	int oldBK = pDc->SetBkMode(m_fontMode);
	COLORREF oldBkColor = pDc->SetBkColor(m_bgColor);

	pDc->TextOut(m_position.x, m_position.y, m_str);
	
	pDc->SelectObject(oldFont);
	pDc->SetTextColor(oldColor);
	pDc->SetBkMode(oldBK);
	pDc->SetBkColor(oldBkColor);
}

int TextDraw::drawType(void) {
	return TEXT;
}

void TextDraw::serialize(CArchive& ar) {
	ar << drawType();
	ar << m_str << m_position << m_fgColor << m_bgColor << m_fontMode << m_fontSize << m_fontName;
}

void TextDraw::deserialize(CArchive& ar) {
	ar >> m_str >> m_position >> m_fgColor >> m_bgColor >> m_fontMode >> m_fontSize >> m_fontName;
}

void TextDraw::insertChar(UINT& nChar) {
	m_str.AppendChar(nChar);
}

void TextDraw::subtractChar(void) {
	if (m_str.GetLength() > 0) {
		m_str.Delete(m_str.GetLength()-1);
	}
}

void TextDraw::setPosition(CPoint& point) {
	m_position = point;
}

CPoint& TextDraw::getPosition() {
	return m_position;
}

CString& TextDraw::getString() {
	return m_str;
}
void TextDraw::setColor(COLORREF& fgColor, COLORREF& bgColor)
{
	m_fgColor = fgColor;
	m_bgColor = bgColor;
}

void TextDraw::setFontSize(int& fontSize)
{
	m_fontSize = fontSize;
}
void TextDraw::setFontName(CString& fontName) {
	m_fontName = fontName;
}

void TextDraw::setFontMode(int& fontMode) {
	m_fontMode = fontMode;
}