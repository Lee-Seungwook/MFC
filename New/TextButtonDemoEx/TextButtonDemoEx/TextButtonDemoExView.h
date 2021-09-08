
// TextButtonDemoExView.h: CTextButtonDemoExView 클래스의 인터페이스
//

#pragma once


class CTextButtonDemoExView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTextButtonDemoExView() noexcept;
	DECLARE_DYNCREATE(CTextButtonDemoExView)

// 특성입니다.
public:
	CTextButtonDemoExDoc* GetDocument() const;
	CRect m_BtnRect;
	CRect m_BtnRect2;
	BOOL m_bClicked;
	BOOL m_bClicked2;

	//흔한 변수 지정
	BOOL draw;
	CPoint startPoint;
	CPoint endPoint;
	CList<CRect, RECT> list;
	//그러하다.

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
	virtual ~CTextButtonDemoExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // TextButtonDemoExView.cpp의 디버그 버전
inline CTextButtonDemoExDoc* CTextButtonDemoExView::GetDocument() const
   { return reinterpret_cast<CTextButtonDemoExDoc*>(m_pDocument); }
#endif

