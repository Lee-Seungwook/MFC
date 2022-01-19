// Tab1.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "Tab1.h"
#include "afxdialogex.h"

#include "VisionImageDlg.h"


// CTab1 대화 상자

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB1, pParent)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_F, m_ListFilter);
}

BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab1::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_F, &CTab1::OnLbnDblclkListF)
END_MESSAGE_MAP()

BOOL CTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ListFilter.InsertString(0, _T("Filter Gaussian"));
	m_ListFilter.InsertString(1, _T("Inverse"));
	m_ListFilter.InsertString(2, _T("Brightness"));
	m_ListFilter.InsertString(3, _T("Contrast"));
	m_ListFilter.InsertString(4, _T("Gamma_Correction"));
	m_ListFilter.InsertString(5, _T("Filter_Laplacian"));
	m_ListFilter.InsertString(6, _T("Filter_UnsharpMask"));
	m_ListFilter.InsertString(7, _T("Filter_Hightboost"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// CTab1 메시지 처리기


void CTab1::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnOK();
}


void CTab1::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnCancel();
}




void CTab1::OnLbnDblclkListF()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_ListFilter.GetCurSel();
	CVisionImageDlg* pMainDlg = (CVisionImageDlg*)AfxGetMainWnd(); // 부모 핸들을 얻음
	pMainDlg->GetIndexF(index); // 부모의 함수를 호출
}
