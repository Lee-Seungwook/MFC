// CannyEdgeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "CannyEdgeDlg.h"
#include "afxdialogex.h"


// CCannyEdgeDlg 대화 상자

IMPLEMENT_DYNAMIC(CCannyEdgeDlg, CDialogEx)

CCannyEdgeDlg::CCannyEdgeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CANNYEDGE, pParent)
	, m_fSigma(1.4f)
	, m_fLowTh(30.0f)
	, m_fMaxTh(60.0f)
{

}

CCannyEdgeDlg::~CCannyEdgeDlg()
{
}

void CCannyEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAUSSIAN_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0, 10);
	DDX_Control(pDX, IDC_GAUSSIAN_SLIDER, m_sliderSigma);
	DDX_Text(pDX, IDC_LOW_EDIT, m_fLowTh);
	DDV_MinMaxFloat(pDX, m_fLowTh, 0, 255);
	DDX_Control(pDX, IDC_LOW_SLIDER, m_sliderLowTh);
	DDX_Text(pDX, IDC_MAX_EDIT, m_fMaxTh);
	DDX_Control(pDX, IDC_MAX_SLIDER, m_sliderMaxTh);
	DDV_MinMaxFloat(pDX, m_fMaxTh, 0, 255);
}


BEGIN_MESSAGE_MAP(CCannyEdgeDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_GAUSSIAN_EDIT, &CCannyEdgeDlg::OnEnChangeGaussianEdit)
	ON_EN_CHANGE(IDC_LOW_EDIT, &CCannyEdgeDlg::OnEnChangeLowEdit)
	ON_EN_CHANGE(IDC_MAX_EDIT, &CCannyEdgeDlg::OnEnChangeMaxEdit)
END_MESSAGE_MAP()


// CCannyEdgeDlg 메시지 처리기


BOOL CCannyEdgeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_sliderSigma.SetRange(10, 250);
	m_sliderSigma.SetTicFreq(20);
	m_sliderSigma.SetPageSize(20);
	m_sliderSigma.SetPos(static_cast<int>(m_fSigma * 50));

	m_sliderLowTh.SetRange(0, 255);
	m_sliderLowTh.SetTicFreq(16);
	m_sliderLowTh.SetPageSize(16);
	m_sliderLowTh.SetPos(30);

	m_sliderMaxTh.SetRange(0, 255);
	m_sliderMaxTh.SetTicFreq(16);
	m_sliderMaxTh.SetPageSize(16);
	m_sliderMaxTh.SetPos(60);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCannyEdgeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderSigma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderSigma.GetPos();
		m_fSigma = (pos / 50.f);
		UpdateData(FALSE);
	}

	else if (m_sliderLowTh.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderLowTh.GetPos();
		m_fLowTh = (float)pos;
		UpdateData(FALSE);
	}

	else if (m_sliderMaxTh.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderMaxTh.GetPos();
		m_fMaxTh = (float)pos;
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CCannyEdgeDlg::OnEnChangeGaussianEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderSigma.SetPos(static_cast<int>(m_fSigma * 50));
}


void CCannyEdgeDlg::OnEnChangeLowEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderLowTh.SetPos(m_fLowTh);
}


void CCannyEdgeDlg::OnEnChangeMaxEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderMaxTh.SetPos(m_fMaxTh);
}
