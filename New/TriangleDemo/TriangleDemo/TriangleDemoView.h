
// TriangleDemoView.h: CTriangleDemoView 클래스의 인터페이스
//

#pragma once


class CTriangleDemoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTriangleDemoView() noexcept;
	DECLARE_DYNCREATE(CTriangleDemoView)

// 특성입니다.
public:
	CTriangleDemoDoc* GetDocument() const;

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
	virtual ~CTriangleDemoView();
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
};

#ifndef _DEBUG  // TriangleDemoView.cpp의 디버그 버전
inline CTriangleDemoDoc* CTriangleDemoView::GetDocument() const
   { return reinterpret_cast<CTriangleDemoDoc*>(m_pDocument); }
#endif

