#pragma once

#include "DrawObject.h"

class ToolbarSetter
{
public:	
	ToolbarSetter(void) {};
	virtual ~ToolbarSetter(void) {};
	virtual void showToolbar(CDialogBar* dialogBar)=0;
	virtual void hideToolbar()=0;
};

/***********************************************/
class LineToolbarSetter : public ToolbarSetter {
private:
	CStatic* m_msgThickness;
	CEdit* m_etThickness;
	CSpinButtonCtrl* m_sbThickness;

public:
	LineToolbarSetter();
	virtual ~LineToolbarSetter();
	void showToolbar(CDialogBar* dialogBar);
	void hideToolbar();
	int getLineWidth();
};

/***********************************************/
class FigureToolbarSetter : public ToolbarSetter {
private:
	CButton* m_btnMode1;
	CButton* m_btnMode2;
	CButton* m_btnMode3;

public:
	FigureToolbarSetter();
	virtual ~FigureToolbarSetter();
	void showToolbar(CDialogBar* dialogBar);
	void hideToolbar();
	FIGURETYPE getFigureType();
};

/***********************************************/
class TextToolbarSetter : public ToolbarSetter {
private:
	CButton* m_btnFont;

	CButton* m_btnMode1;
	CButton* m_btnMode2;

public:
	TextToolbarSetter();
	virtual ~TextToolbarSetter();
	void showToolbar(CDialogBar* dialogBar);
	void hideToolbar();
	int getOpacity();
};


///***********************************************/
//class BeeLineToolbarSetter : public ToolbarSetter {
//
//public:
//	BeeLineToolbarSetter();
//	virtual ~BeeLineToolbarSetter();
//	void showToolbar(CDialogBar& dialogBar);
//	void hideToolbar();
//};
//
///***********************************************/
//class CircleToolbarSetter : public ToolbarSetter {
//public:
//	CircleToolbarSetter();
//	virtual ~CircleToolbarSetter();
//	void showToolbar(CDialogBar& dialogBar);
//	void hideToolbar();
//};
//
///***********************************************/
//class RectangleToolbarSetter : public ToolbarSetter {
//public:
//	RectangleToolbarSetter();
//	virtual ~RectangleToolbarSetter();
//	void showToolbar(CDialogBar& dialogBar);
//	void hideToolbar();
//};
//
///***********************************************/
//class PolygonToolbarSetter : public ToolbarSetter {
//
//public:
//	PolygonToolbarSetter();
//	virtual ~PolygonToolbarSetter();
//	void showToolbar(CDialogBar& dialogBar);
//	void hideToolbar();
//};