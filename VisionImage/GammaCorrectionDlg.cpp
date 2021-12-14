﻿// GammaCorrectionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "GammaCorrectionDlg.h"
#include "afxdialogex.h"


// CGammaCorrectionDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaCorrectionDlg, CDialogEx)

CGammaCorrectionDlg::CGammaCorrectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMMACORRECTION, pParent)
	, m_fGamma(2.20f)
{

}

CGammaCorrectionDlg::~CGammaCorrectionDlg()
{
}

void CGammaCorrectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAMMA_EDIT, m_fGamma);
	DDV_MinMaxFloat(pDX, m_fGamma, 0.20f, 5.00f);
	DDX_Control(pDX, IDC_GAMMA_SLIDER, m_sliderGamma);
}


BEGIN_MESSAGE_MAP(CGammaCorrectionDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_GAMMA_EDIT, &CGammaCorrectionDlg::OnChangeGammaEdit)
END_MESSAGE_MAP()


// CGammaCorrectionDlg 메시지 처리기


BOOL CGammaCorrectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	// 슬라이더 컨트롤 초기화
	m_sliderGamma.SetRange(10, 250);
	m_sliderGamma.SetTicFreq(20);
	m_sliderGamma.SetPageSize(20);
	m_sliderGamma.SetPos(static_cast<int>(m_fGamma * 50)); // 실수값을 정숫값으로 바꾸어 슬라이더 컨트롤에 대입

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGammaCorrectionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderGamma.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int pos = m_sliderGamma.GetPos();
		m_fGamma = (pos / 50.f); // 정수형 슬라이더 컨트롤을 실수형으로 변경하여 Edit 컨트롤 변수에 저장
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CGammaCorrectionDlg::OnChangeGammaEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderGamma.SetPos(static_cast<int>(m_fGamma * 50));  // 실수값을 정숫값으로 바꾸어 슬라이더 컨트롤에 대입
}
