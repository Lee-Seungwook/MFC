
// SEditGraphicDoc.cpp: CSEditGraphicDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SEditGraphic.h"
#endif

#include "SEditGraphicDoc.h"

#include <propkey.h>
#include "TextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define BLUE RGB(51,51,255)
#define YELLOW RGB(255,204,51)

// CSEditGraphicDoc

IMPLEMENT_DYNCREATE(CSEditGraphicDoc, CDocument)

BEGIN_MESSAGE_MAP(CSEditGraphicDoc, CDocument)
	ON_COMMAND(ID_DATA_INPUT, &CSEditGraphicDoc::OnDataInput)
	ON_COMMAND(ID__COLOR_BLUE, &CSEditGraphicDoc::OnColorBlue)
	ON_COMMAND(ID__COLOR_YELLOW, &CSEditGraphicDoc::OnColorYellow)
	ON_COMMAND(ID_COLOR_RED, &CSEditGraphicDoc::OnColorRed)
END_MESSAGE_MAP()


// CSEditGraphicDoc 생성/소멸

CSEditGraphicDoc::CSEditGraphicDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSEditGraphicDoc::~CSEditGraphicDoc()
{
}

BOOL CSEditGraphicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSEditGraphicDoc serialization

void CSEditGraphicDoc::Serialize(CArchive& ar)
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
void CSEditGraphicDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSEditGraphicDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSEditGraphicDoc::SetSearchContent(const CString& value)
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

// CSEditGraphicDoc 진단

#ifdef _DEBUG
void CSEditGraphicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSEditGraphicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSEditGraphicDoc 명령


CString CSEditGraphicDoc::GetText()
{
	// TODO: 여기에 구현 코드 추가.
	return m_strData;
}


void CSEditGraphicDoc::SetText(CString strInput)
{
	// TODO: 여기에 구현 코드 추가.
	m_strData = strInput;
	UpdateAllViews(NULL); // 모든 뷰를 갱신한다.
}


void CSEditGraphicDoc::OnDataInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CTextDlg m_TextDlg;
	m_TextDlg.m_strTextInput = GetText();

	if (m_TextDlg.DoModal() == IDOK) {
		SetText(m_TextDlg.m_strTextInput);
	}
	// 입력 다이얼로그박스에서 입력된 내용을 화면상에 나타낸다.
}


void CSEditGraphicDoc::ColorSet(COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	m_curColor = color;
	UpdateAllViews(NULL);
}


COLORREF CSEditGraphicDoc::ColorGet()
{
	// TODO: 여기에 구현 코드 추가.
	return m_curColor;
}


void CSEditGraphicDoc::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(BLUE);
}


void CSEditGraphicDoc::OnColorYellow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(YELLOW);
}


void CSEditGraphicDoc::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ColorSet(RED);
}
