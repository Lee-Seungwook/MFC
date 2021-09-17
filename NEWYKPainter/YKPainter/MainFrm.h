// MainFrm.h : CMainFrame 클래스의 인터페이스
//


#pragma once

#include "ChildView.h"
#include "ToolbarDialog.h"
#include "ToolbarSetter.h"
#include "DrawObject.h"

class CMainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)

public:
	CMainFrame();
	virtual ~CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CStatusBar  m_wndStatusBar;

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar    m_wndToolBar;
	ToolbarDialog	m_wndDialogBar;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	LRESULT OnSelTool(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};