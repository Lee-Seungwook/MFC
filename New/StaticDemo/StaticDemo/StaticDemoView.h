
// StaticDemoView.h: CStaticDemoView 클래스의 인터페이스
//

#pragma once


class CStaticDemoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CStaticDemoView() noexcept;
	DECLARE_DYNCREATE(CStaticDemoView)

// 특성입니다.
public:
	CStaticDemoDoc* GetDocument() const;
	CStatic m_wndStatic; // 스태틱 컨트롤 윈도우
	CStatic m_wndStatic2; // 아이콘 이미지 출력

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
	virtual ~CStaticDemoView();
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
};

#ifndef _DEBUG  // StaticDemoView.cpp의 디버그 버전
inline CStaticDemoDoc* CStaticDemoView::GetDocument() const
   { return reinterpret_cast<CStaticDemoDoc*>(m_pDocument); }
#endif

