
// KeyMove1View.cpp: CKeyMove1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "KeyMove1.h"
#endif

#include "KeyMove1Doc.h"
#include "KeyMove1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int a = 0;
int b = 0;


// CKeyMove1View

IMPLEMENT_DYNCREATE(CKeyMove1View, CView)

BEGIN_MESSAGE_MAP(CKeyMove1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CKeyMove1View 생성/소멸

CKeyMove1View::CKeyMove1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CKeyMove1View::~CKeyMove1View()
{
}

BOOL CKeyMove1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CKeyMove1View 그리기

void CKeyMove1View::OnDraw(CDC* /*pDC*/)
{
	CKeyMove1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CKeyMove1View 인쇄

BOOL CKeyMove1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CKeyMove1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CKeyMove1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CKeyMove1View 진단

#ifdef _DEBUG
void CKeyMove1View::AssertValid() const
{
	CView::AssertValid();
}

void CKeyMove1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKeyMove1Doc* CKeyMove1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeyMove1Doc)));
	return (CKeyMove1Doc*)m_pDocument;
}
#endif //_DEBUG


// CKeyMove1View 메시지 처리기


int CKeyMove1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndChild.Create(TEXT("STATIC"), TEXT("KeyMove"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(100, 100, 200, 200), this, 1234);

	return 0;
}


void CKeyMove1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint ptChild; // 차일드 윈도우의 좌표
	CRect Rect; // 차일드 윈도우의 좌표 및 크기

	// 차일드 윈도우의 두 좌표 정보를 알아 온다.
	m_wndChild.GetWindowRect(&Rect);
	ptChild.x = Rect.right;
	ptChild.y = Rect.bottom;

	// 스크린 기준 좌표를 클라이언트 뷰 기준의 좌표로 환산
	ScreenToClient(&ptChild);

	WORD wResult = ::GetKeyState(VK_CONTROL);
	BYTE byHigh = HIBYTE(wResult);
	// 상위 바이트의 1번 비트가 1이면 키가 눌려진 상태
	if (byHigh & 0x01) {
		switch (nChar)
		{
		case VK_LEFT:
			ptChild.x -= 10 * 2;
			break;

		case VK_RIGHT:
			ptChild.x += 10 * 2;
			break;

		case VK_UP:
			ptChild.y -= 10 * 2;
			break;

		case VK_DOWN:
			ptChild.y += 10 * 2;
			break;
		}
	}
	else {
		switch (nChar)
		{
		case VK_LEFT:
			ptChild.x -= 10;
			break;

		case VK_RIGHT:
			ptChild.x += 10;
			break;

		case VK_UP:
			ptChild.y -= 10;
			break;

		case VK_DOWN:
			ptChild.y += 10;
			break;
		}

	}

	
		/*switch (nChar)
		{
		case VK_LEFT:
			a-= 10;
			break;

		case VK_RIGHT:
			a+= 10;
			break;

		case VK_UP:
			b-= 10;
			break;

		case VK_DOWN:
			b+= 10;
			break;
		}
*/



	// 변경된 새 좌표로 차일드 윈도우를 이동시킨다.
	m_wndChild.SetWindowPos(&CWnd::wndTop, 100, 100, ptChild.x, ptChild.y, SWP_SHOWWINDOW | SWP_NOZORDER);


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CKeyMove1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strText = TEXT("");
	strText.Format(TEXT("%c"), nChar);

	// 입력한 키가 Enter, Back Space, ESC 키가 아니면
	// 해당 ASCII 문자로 차일드 윈도우 텍스트를 변경
	if (nChar != VK_RETURN && nChar != VK_BACK && nChar != VK_ESCAPE) {
		m_wndChild.SetWindowText(strText);
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CKeyMove1View::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strMessage = TEXT("");

	// space 키에 대한 상태 정보를 수집
	WORD wResult = ::GetKeyState(VK_SPACE);
	BYTE byHigh = HIBYTE(wResult);
	// 상위 바이트의 1번 비트가 1이면 키가 눌려진 상태
	if (byHigh & 0x01) {
		strMessage += TEXT("ALT + SPACE, ");

		// 같은 방법으로 Caps LOCK 키의 상태를 검사
		wResult = ::GetKeyState(VK_CAPITAL);
		// 하위 바이트의 1번 비트가 1이면 토글 키가 켜진 상태
		BYTE byLow = LOBYTE(wResult);

		if (byLow & 0x01)
			strMessage += TEXT("CAPS LOCK ON");
		else 
			strMessage += TEXT("CAPS LOCK OFF");

		AfxMessageBox(strMessage);
	}

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


void CKeyMove1View::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_RETURN)
		AfxMessageBox(TEXT("ALT + ENTER"));
	else if (nChar == 's' || nChar == 'S')
		AfxMessageBox(TEXT("ALT + S"));
	else if (nChar == 'x' || nChar == 'X')
		AfxMessageBox(TEXT("ALT + X"));

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}


void CKeyMove1View::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnClose();
}
