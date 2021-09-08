#include "pch.h"
#include "TrackWnd.h"

IMPLEMENT_DYNAMIC(CTrackWnd, CWnd)

CTrackWnd::CTrackWnd() {
	m_bTrack = FALSE;
}

CTrackWnd::~CTrackWnd() {

}
BEGIN_MESSAGE_MAP(CTrackWnd, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


void CTrackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bTrack == FALSE) {
		TRACKMOUSEEVENT MouseEvent;
		::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

		MouseEvent.cbSize = sizeof(MouseEvent);
		MouseEvent.dwFlags = TME_LEAVE;
		MouseEvent.hwndTrack = m_hWnd;
		MouseEvent.dwHoverTime = 0;

		m_bTrack = ::_TrackMouseEvent(&MouseEvent);
		if (m_bTrack) {
			SetWindowText(TEXT("Tracking!"));
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CTrackWnd::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACKMOUSEEVENT MouseEvent;
	:: ZeroMemory(&MouseEvent, sizeof(MouseEvent));
	MouseEvent.cbSize = sizeof(MouseEvent);
	MouseEvent.dwFlags = TME_CANCEL;
	MouseEvent.hwndTrack = m_hWnd;

	::_TrackMouseEvent(&MouseEvent);

	m_bTrack = FALSE;
	SetWindowText(TEXT("WM_MOUSELEAVE"));

	CWnd::OnMouseLeave();
}
