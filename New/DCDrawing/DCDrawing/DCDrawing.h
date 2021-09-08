
// DCDrawing.h: DCDrawing 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 주 기호입니다.


// CDCDrawingApp:
// 이 클래스의 구현에 대해서는 DCDrawing.cpp을(를) 참조하세요.
//

class CDCDrawingApp : public CWinAppEx
{
public:
	CDCDrawingApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDCDrawingApp theApp;
