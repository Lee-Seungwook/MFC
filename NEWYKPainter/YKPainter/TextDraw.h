#pragma once
#include "drawobject.h"

class TextDraw : 
	public DrawObject
{
private:
	CString m_str;
	CPoint m_position;
	COLORREF m_fgColor, m_bgColor;
	int m_fontSize;
	CString m_fontName;
	int m_fontMode;

public:
	TextDraw(void);
	virtual ~TextDraw(void);
	void draw(CDC* pDc);
	int drawType(void);
	void serialize(CArchive& ar);
	void deserialize(CArchive& ar);

	void insertChar(UINT& nChar);
	void subtractChar(void);
	void setPosition(CPoint& point);
	CPoint& getPosition();
	CString& getString();
	void setColor(COLORREF& fgColor, COLORREF& bgColor);
	void setFontSize(int& fontSize);
	void setFontName(CString& fontName);
	void setFontMode(int& fontMode);
};
