// Tab2.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "Tab2.h"
#include "afxdialogex.h"

#include "VisionImageDlg.h"


// CTab2 대화 상자

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB2, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_I, m_ListBinary);
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab2::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_I, &CTab2::OnLbnDblclkListI)
END_MESSAGE_MAP()


// CTab2 메시지 처리기


void CTab2::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnOK();
}


void CTab2::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnCancel();
}


BOOL CTab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ListBinary.InsertString(0, _T("Binary"));
	m_ListBinary.InsertString(1, _T("Rotate"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTab2::OnLbnDblclkListI()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_ListBinary.GetCurSel();
	CVisionImageDlg* pMainDlg = (CVisionImageDlg*)AfxGetMainWnd(); // 부모 핸들을 얻음


	pMainDlg->GetIndexI(index);
}
