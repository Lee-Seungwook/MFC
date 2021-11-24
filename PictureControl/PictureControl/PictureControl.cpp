// PictureControl.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
#include "pch.h"
#include "framework.h"
#include "PictureControl.h"
#include "PictureControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPictureControlApp
BEGIN_MESSAGE_MAP(CPictureControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CPictureControlApp 생성
CPictureControlApp::CPictureControlApp()
{
}

// 유일한 CPictureControlApp 개체입니다.
CPictureControlApp theApp;

// CPictureControlApp 초기화
BOOL CPictureControlApp::InitInstance()
{
	CWinApp::InitInstance();

	CPictureControlDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}