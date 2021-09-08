#pragma once
#include <afxwin.h>
class CTrackWnd : public CWnd
{
	DECLARE_DYNAMIC(CTrackWnd)
	
public:
	CTrackWnd();
	virtual ~CTrackWnd();

	BOOL m_bTrack;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};

