
// KeyMove1View.h: CKeyMove1View 클래스의 인터페이스
//

#pragma once


class CKeyMove1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CKeyMove1View() noexcept;
	DECLARE_DYNCREATE(CKeyMove1View)

// 특성입니다.
public:
	CKeyMove1Doc* GetDocument() const;

// 작업입니다.
public:
	CWnd m_wndChild;

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
	virtual ~CKeyMove1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // KeyMove1View.cpp의 디버그 버전
inline CKeyMove1Doc* CKeyMove1View::GetDocument() const
   { return reinterpret_cast<CKeyMove1Doc*>(m_pDocument); }
#endif

