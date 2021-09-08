
// SEditGraphic1Doc.cpp: CSEditGraphic1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SEditGraphic1.h"
#endif

#include "SEditGraphic1Doc.h"

#include <propkey.h>
#include "TextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define BLUE RGB(51,51,255)
#define YELLOW RGB(255,204,51)


// CSEditGraphic1Doc

IMPLEMENT_DYNCREATE(CSEditGraphic1Doc, CDocument)

BEGIN_MESSAGE_MAP(CSEditGraphic1Doc, CDocument)
	ON_COMMAND(ID_DATA_INPUT, &CSEditGraphic1Doc::OnDataInput)
	ON_COMMAND(ID_COLOR_BLUE, &CSEditGraphic1Doc::OnColorBlue)
	ON_COMMAND(ID_COLOR_RED, &CSEditGraphic1Doc::OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, &CSEditGraphic1Doc::OnColorYellow)
END_MESSAGE_MAP()


// CSEditGraphic1Doc 생성/소멸

CSEditGraphic1Doc::CSEditGraphic1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSEditGraphic1Doc::~CSEditGraphic1Doc()
{
}

BOOL CSEditGraphic1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSEditGraphic1Doc serialization

void CSEditGraphic1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSEditGraphic1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSEditGraphic1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSEditGraphic1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSEditGraphic1Doc 진단

#ifdef _DEBUG
void CSEditGraphic1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSEditGraphic1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSEditGraphic1Doc 명령


CString CSEditGraphic1Doc::GetText()
{
	// TODO: 여기에 구현 코드 추가.
	return m_strData;
}


void CSEditGraphic1Doc::SetText(CString strInput)
{
	// TODO: 여기에 구현 코드 추가.
	m_strData = strInput;
	UpdateAllViews(NULL); // 모든 View 갱신

}


void CSEditGraphic1Doc::OnDataInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTextDlg m_TextDlg;
	m_TextDlg.m_strTextInput = GetText();

	if (m_TextDlg.DoModal() == IDOK) {
		SetText(m_TextDlg.m_strTextInput);
	}
	// 입력 다이얼로그박스에서 입력된 내용을 화면상에 나타낸다.
}


void CSEditGraphic1Doc::ColorSet(COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	m_curColor = color;
	UpdateAllViews(NULL);
}

COLORREF CSEditGraphic1Doc::ColorGet()
{
	// TODO: 여기에 구현 코드 추가.
	return m_curColor;
}


void CSEditGraphic1Doc::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(BLUE);
}


void CSEditGraphic1Doc::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(RED);
}


void CSEditGraphic1Doc::OnColorYellow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(YELLOW);
}
