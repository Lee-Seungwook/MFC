// ToolbarDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YKPainter.h"
#include "ToolbarDialog.h"

#include "MainFrm.h"
#include "ChildView.h"

#include "ToolValues.h"
// ToolbarDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(ToolbarDialog, CDialogBar)

BEGIN_MESSAGE_MAP(ToolbarDialog, CDialogBar)
	ON_EN_CHANGE(ID_EDIT_LINEWIDTH, OnEditChange)
	ON_BN_CLICKED(ID_RB_DRAWTYPE, OnRBClicked)
	ON_BN_CLICKED(ID_BTN_FONT, OnBtnFontClicked)
	ON_BN_CLICKED(ID_BTN_FONT_MODE, OnBtnFontModeClicked)
	ON_COMMAND(ID_CMD_FGCOLOR, OnFgClick)
	ON_COMMAND(ID_CMD_BGCOLOR, OnBgClick)
	ON_UPDATE_COMMAND_UI(ID_BTN_FONT, OnBtnFontUpdateUI)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()


ToolbarDialog::ToolbarDialog(CWnd* pParent /*=NULL*/)
	: CDialogBar()
{
	m_lineSetter	= new LineToolbarSetter();
	m_figureSetter	= new FigureToolbarSetter();
	m_textSetter	= new TextToolbarSetter();
}

ToolbarDialog::~ToolbarDialog() {
	delete m_lineSetter;
	delete m_figureSetter;
	delete m_textSetter;
}

void ToolbarDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}

void ToolbarDialog::OnBtnFontUpdateUI(CCmdUI* pCmdUI) {
	pCmdUI->Enable();
}

int ToolbarDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_fgColorBox.Create("", WS_DLGFRAME | WS_VISIBLE | WS_CHILD | SS_ENHMETAFILE | SS_NOTIFY, CRect(15, 5, 40, 32), this, ID_CMD_FGCOLOR)) {
		return -1;
	}

	if (!m_bgColorBox.Create("", WS_DLGFRAME | WS_VISIBLE | WS_CHILD | SS_ENHMETAFILE | SS_NOTIFY, CRect(45, 5, 70, 32), this, ID_CMD_BGCOLOR)) {
		return -1;
	}

	m_fgColorBox.ShowWindow(SW_SHOW);
	m_bgColorBox.ShowWindow(SW_SHOW);

	return 0;
}

HBRUSH ToolbarDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	TRACE("ToolbarDialog::OnCtlColor()\n");
	HBRUSH hbr = CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	if (m_fgColorBox.GetSafeHwnd() == pWnd->GetSafeHwnd()) {
		hbr = ::CreateSolidBrush(ToolValues::FgColor);
	}
	if (m_bgColorBox.GetSafeHwnd() == pWnd->GetSafeHwnd()) {
		hbr = ::CreateSolidBrush(ToolValues::BgColor);	
	}
	
//	if (pWnd->GetDlgCtrlID() == 504) {
//		pWnd->EnableWindow(TRUE);
//	}

	return hbr;
}


void ToolbarDialog::OnBgClick(void)
{
	TRACE("ToolbarDialog::OnBgClick\n");

	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		ToolValues::BgColor = dlg.GetColor();
		Invalidate(TRUE);
	}
}

void ToolbarDialog::OnFgClick(void)
{
	TRACE("ToolbarDialog::OnFgClick\n");
	CColorDialog dlg;
	
	if (dlg.DoModal()) {
		ToolValues::FgColor = dlg.GetColor();
		Invalidate(TRUE);
	}
}

void ToolbarDialog::OnEditChange() {
	ToolValues::LineWidth = m_lineSetter->getLineWidth();
	TRACE("ToolbarDialog::LOnEditChange(%d)\n", ToolValues::LineWidth);
}

void ToolbarDialog::OnRBClicked() {
	ToolValues::FigureType = m_figureSetter->getFigureType();
}

void ToolbarDialog::OnBtnFontClicked() {
	TRACE("ToolbarDialog::OnBtnFontClicked()\n");
	LOGFONT logFont;
	int size;
	CFontDialog dlg;
	if (dlg.DoModal() == IDOK) {
		
		dlg.GetCurrentFont(&logFont);

		ToolValues::FontName = logFont.lfFaceName;
		ToolValues::FontSize = dlg.GetSize();
	}
}

void ToolbarDialog::OnBtnFontModeClicked() {
	TRACE("OnBtnFontModeClicked()\n");

	ToolValues::FontMode = m_textSetter->getOpacity();
}

void ToolbarDialog::showTools(TOOLTYPE type)
{
	m_lineSetter->hideToolbar();
	m_figureSetter->hideToolbar();
	m_textSetter->hideToolbar();

	if (type == PENCIL || type == BEELINE) {
		m_lineSetter->showToolbar(this);
	}
	if (type == CIRCLE || type == RECTANGLE || type == POLYGON) {
		m_lineSetter->showToolbar(this);
		m_figureSetter->showToolbar(this);
	}
	if (type == TEXT) {
		m_textSetter->showToolbar(this);
	}
}