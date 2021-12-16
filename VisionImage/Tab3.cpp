// Tab3.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "Tab3.h"
#include "afxdialogex.h"

#include "VisionImageDlg.h"


// CTab3 대화 상자

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB3, pParent)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_D, m_ListDetect);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTab3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTab3::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_D, &CTab3::OnLbnDblclkListD)
END_MESSAGE_MAP()


// CTab3 메시지 처리기
BOOL CTab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ListDetect.InsertString(0, _T("EdgeRoberts"));
	m_ListDetect.InsertString(1, _T("EdgePrewitt"));
	m_ListDetect.InsertString(2, _T("EdgeSobel"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTab3::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnOK();
}


void CTab3::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// CDialogEx::OnCancel();
}

void CTab3::OnLbnDblclkListD()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_ListDetect.GetCurSel();
	CVisionImageDlg* pMainDlg = (CVisionImageDlg*)AfxGetMainWnd(); // 부모 핸들을 얻음
	pMainDlg->GetIndexD(index);
}
