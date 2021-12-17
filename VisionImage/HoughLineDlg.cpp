// HoughLineDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "HoughLineDlg.h"
#include "afxdialogex.h"


// CHoughLineDlg 대화 상자

IMPLEMENT_DYNAMIC(CHoughLineDlg, CDialogEx)

CHoughLineDlg::CHoughLineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOUGHLINE_CANNY, pParent)
{

}

CHoughLineDlg::~CHoughLineDlg()
{
}

void CHoughLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_HGAUSSIAN_EDIT, m_fSigmaH);
	DDV_MinMaxFloat(pDX, m_fSigmaH, 0, 10);
	DDX_Control(pDX, IDC_HGAUSSIAN_SLIDER, m_sliderSigmaH);
	DDX_Text(pDX, IDC_HLOW_EDIT, m_fLowThH);
	DDV_MinMaxFloat(pDX, m_fLowThH, 0, 255);
	DDX_Control(pDX, IDC_HLOW_SLIDER, m_sliderLowThH);
	DDX_Text(pDX, IDC_HMAX_EDIT, m_fMaxThH);
	DDX_Control(pDX, IDC_HMAX_SLIDER, m_sliderMaxThH);
	DDV_MinMaxFloat(pDX, m_fMaxThH, 0, 255);
}


BEGIN_MESSAGE_MAP(CHoughLineDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_HGAUSSIAN_EDIT, &CHoughLineDlg::OnEnChangeHgaussianEdit)
	ON_EN_CHANGE(IDC_HLOW_EDIT, &CHoughLineDlg::OnEnChangeHlowEdit)
	ON_EN_CHANGE(IDC_HMAX_EDIT, &CHoughLineDlg::OnEnChangeHmaxEdit)
END_MESSAGE_MAP()


// CHoughLineDlg 메시지 처리기


BOOL CHoughLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_sliderSigmaH.SetRange(10, 250);
	m_sliderSigmaH.SetTicFreq(20);
	m_sliderSigmaH.SetPageSize(20);
	m_sliderSigmaH.SetPos(static_cast<int>(m_fSigmaH * 50));

	m_sliderLowThH.SetRange(0, 255);
	m_sliderLowThH.SetTicFreq(16);
	m_sliderLowThH.SetPageSize(16);
	m_sliderLowThH.SetPos(30);

	m_sliderMaxThH.SetRange(0, 255);
	m_sliderMaxThH.SetTicFreq(16);
	m_sliderMaxThH.SetPageSize(16);
	m_sliderMaxThH.SetPos(60);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHoughLineDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderSigmaH.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderSigmaH.GetPos();
		m_fSigmaH = (pos / 50.f);
		UpdateData(FALSE);
	}

	else if (m_sliderLowThH.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderLowThH.GetPos();
		m_fLowThH = (float)pos;
		UpdateData(FALSE);
	}

	else if (m_sliderMaxThH.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderMaxThH.GetPos();
		m_fMaxThH = (float)pos;
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CHoughLineDlg::OnEnChangeHgaussianEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderSigmaH.SetPos(static_cast<int>(m_fSigmaH * 50));
}


void CHoughLineDlg::OnEnChangeHlowEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderLowThH.SetPos(m_fLowThH);
}


void CHoughLineDlg::OnEnChangeHmaxEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderMaxThH.SetPos(m_fMaxThH);
}
