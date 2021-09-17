#include "StdAfx.h"
#include "ToolbarSetter.h"

/****************************************************
 * PencilToolBarSetter
 ****************************************************/
LineToolbarSetter::LineToolbarSetter() {;
	m_msgThickness = NULL;
	m_sbThickness = NULL;
	m_etThickness = NULL;
}

LineToolbarSetter::~LineToolbarSetter() {
	if (m_etThickness != NULL) { delete m_etThickness; }
	if (m_msgThickness != NULL) { delete m_msgThickness; }
	if (m_sbThickness != NULL) { delete m_sbThickness; }
}

void LineToolbarSetter::showToolbar(CDialogBar* dialogBar) {
	TRACE("PencilToolbarSetter : setToolbar()\n");

	if (m_msgThickness == NULL) {
		m_msgThickness = new CStatic;
		m_msgThickness->Create("선굵기", WS_VISIBLE | WS_CHILD | SS_CENTER, CRect(108, 12, 170, 30), dialogBar);
	}
	if (m_etThickness == NULL){ 
		m_etThickness = new CEdit;
		m_etThickness->Create(ES_CENTER | ES_NUMBER, CRect(165, 11, 240, 31), dialogBar, 502);
		
				
		m_sbThickness = new CSpinButtonCtrl;
		m_sbThickness->Create(UDS_ALIGNRIGHT | UDS_SETBUDDYINT | UDS_AUTOBUDDY | UDS_ARROWKEYS, CRect(0, 0, 0, 0), dialogBar, 0);
		m_sbThickness->SetBuddy(m_etThickness);
		m_sbThickness->SetRange(1, 100);
		
	
	}
	m_sbThickness->SetPos(1);
	m_etThickness->ShowWindow(SW_SHOW);
	m_sbThickness->ShowWindow(SW_SHOW);
	m_msgThickness->ShowWindow(SW_SHOW);
}

void LineToolbarSetter::hideToolbar() {
	if (m_msgThickness != NULL) { m_msgThickness->ShowWindow(SW_HIDE); }
	if (m_etThickness != NULL) { m_etThickness->ShowWindow(SW_HIDE); }
	if (m_sbThickness != NULL) { m_sbThickness->ShowWindow(SW_HIDE); }
}

int LineToolbarSetter::getLineWidth() {
	CString val;
	m_etThickness->GetWindowText(val);
	
	return _ttoi(val);
}

/**************************************************
* FillToolbarSetter
*************************************************/
FigureToolbarSetter::FigureToolbarSetter() {
	m_btnMode1 = NULL;
	m_btnMode2 = NULL;
	m_btnMode3 = NULL;
}

FigureToolbarSetter::~FigureToolbarSetter() {
	if (m_btnMode1 != NULL) { delete m_btnMode1; }
	if (m_btnMode2 != NULL) { delete m_btnMode2; }
	if (m_btnMode3 != NULL) { delete m_btnMode3; }
}

void FigureToolbarSetter::showToolbar(CDialogBar* dialogBar) {
	if (m_btnMode1 == NULL) {
		m_btnMode1 = new CButton;
		m_btnMode1->Create("채우기 없음", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(250, 11, 360, 31), dialogBar, 503);
	}
	if (m_btnMode2 == NULL) {
		m_btnMode2 = new CButton;
		m_btnMode2->Create("채우기", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(360, 11, 430, 31), dialogBar, 503);
	}
	if (m_btnMode3 == NULL) {
		m_btnMode3 = new CButton;
		m_btnMode3->Create("선 없음", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CRect(430, 11, 510, 31), dialogBar, 503);
	}

	m_btnMode1->SetCheck(BST_CHECKED);
	m_btnMode2->SetCheck(BST_UNCHECKED);
	m_btnMode3->SetCheck(BST_UNCHECKED);
	m_btnMode1->ShowWindow(SW_SHOW);
	m_btnMode2->ShowWindow(SW_SHOW);
	m_btnMode3->ShowWindow(SW_SHOW);
}

void FigureToolbarSetter::hideToolbar() {
	if (m_btnMode1 != NULL) { m_btnMode1->ShowWindow(SW_HIDE); }
	if (m_btnMode2 != NULL) { m_btnMode2->ShowWindow(SW_HIDE); }
	if (m_btnMode3 != NULL) { m_btnMode3->ShowWindow(SW_HIDE); }
}

FIGURETYPE FigureToolbarSetter::getFigureType() {
	if (m_btnMode1->GetCheck()) {
		return BORDERONLY;
	}
	if (m_btnMode2->GetCheck()) {
		return BORDERFILL;
	}
	if (m_btnMode3->GetCheck()) {
		return NOBORDERFILL;
	}
}

/**************************************************
* TextToolbarSetter
*************************************************/
TextToolbarSetter::TextToolbarSetter() {
	m_btnFont = NULL;
	m_btnMode1 = NULL;
	m_btnMode2 = NULL;
}

TextToolbarSetter::~TextToolbarSetter() {
	if (m_btnFont != NULL) { delete m_btnFont; }
	if (m_btnMode1 != NULL) { delete m_btnMode1; }
	if (m_btnMode2 != NULL) { delete m_btnMode2; }
}

void TextToolbarSetter::showToolbar(CDialogBar* dialogBar) {
	if (m_btnFont == NULL) {
		m_btnFont = new CButton();
		m_btnFont->Create("Font..", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(120, 5, 170, 30), dialogBar, 504);
	}
	if (m_btnMode1 == NULL) {
		m_btnMode1 = new CButton;
		m_btnMode1->Create("배경없음", WS_CHILD | WS_VISIBLE |  BS_AUTORADIOBUTTON, CRect(190, 5, 290, 30), dialogBar, 505);
	}
	if (m_btnMode2 == NULL) {
		m_btnMode2 = new CButton;
		m_btnMode2->Create("배경채움", WS_CHILD | WS_VISIBLE |  BS_AUTORADIOBUTTON, CRect(300, 5, 410, 30), dialogBar, 505);
	}
	m_btnFont->ShowWindow(SW_SHOW);
	m_btnFont->EnableWindow(TRUE);
	m_btnMode1->SetCheck(BST_CHECKED);
	m_btnMode2->SetCheck(BST_UNCHECKED);
	m_btnMode1->ShowWindow(SW_SHOW);
	m_btnMode2->ShowWindow(SW_SHOW);
}

void TextToolbarSetter::hideToolbar() {
	if (m_btnFont != NULL) { m_btnFont->ShowWindow(SW_HIDE); }
	if (m_btnMode1 != NULL) { m_btnMode1->ShowWindow(SW_HIDE); }
	if (m_btnMode2 != NULL) { m_btnMode2->ShowWindow(SW_HIDE); }
}

int TextToolbarSetter::getOpacity() {
	if (m_btnMode1->GetCheck()) {
		return TRANSPARENT;
	}
	return OPAQUE;
}