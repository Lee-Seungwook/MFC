#pragma once

#include "ToolbarSetter.h"
#include "DrawObject.h"

// ToolbarDialog 대화 상자입니다.

class ToolbarDialog : public CDialogBar
{
	DECLARE_DYNAMIC(ToolbarDialog)

private:
	CStatic m_fgColorBox, m_bgColorBox;

	LineToolbarSetter* m_lineSetter;
	FigureToolbarSetter* m_figureSetter;
	TextToolbarSetter* m_textSetter;

public:
	ToolbarDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ToolbarDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditChange();
	afx_msg void OnRBClicked();
	afx_msg void OnBtnFontClicked();
	afx_msg void OnBtnFontModeClicked();
	afx_msg void OnBtnFontUpdateUI(CCmdUI* pCmdUI);

protected:
	void OnBgClick(void);
	void OnFgClick(void);
public:
	void showTools(TOOLTYPE type);
};
