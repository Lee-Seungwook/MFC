
// DrawModeDemoView.h: CDrawModeDemoView 클래스의 인터페이스
//

#pragma once


class CDrawModeDemoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDrawModeDemoView() noexcept;
	DECLARE_DYNCREATE(CDrawModeDemoView)

// 특성입니다.
public:
	CDrawModeDemoDoc* GetDocument() const;

	CPoint m_ptBegin; // 붉은 실선의 시작 좌표
	CPoint m_ptEnd; // 붉은 실선의 끝 좌표
	CPoint m_ptDragBegin; // 드래그가 시작된 좌표
	CPoint m_ptDragEnd; // 드래그가 진행 중인 좌표

	

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CDrawModeDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawInvertLine(CPoint point);
//	afx_msg void OnDrawClipboard();
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // DrawModeDemoView.cpp의 디버그 버전
inline CDrawModeDemoDoc* CDrawModeDemoView::GetDocument() const
   { return reinterpret_cast<CDrawModeDemoDoc*>(m_pDocument); }
#endif

