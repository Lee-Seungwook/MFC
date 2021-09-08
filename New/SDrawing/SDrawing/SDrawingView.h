
// SDrawingView.h: CSDrawingView 클래스의 인터페이스
//

#pragma once


class CSDrawingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSDrawingView() noexcept;
	DECLARE_DYNCREATE(CSDrawingView)

// 특성입니다.
public:
	CSDrawingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CSDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int m_ptX;
	int m_ptY;
	int m_crColor;
	CRect m_reRect;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SDrawingView.cpp의 디버그 버전
inline CSDrawingDoc* CSDrawingView::GetDocument() const
   { return reinterpret_cast<CSDrawingDoc*>(m_pDocument); }
#endif

