// BrightnessDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "BrightnessDlg.h"
#include "afxdialogex.h"

#include "IppImage.h"
#include "IppEnhance.h"
#include "IppConvert.h"
#include "ImageSize.h"


// CBrightnessDlg 대화 상자

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx)

CBrightnessDlg::CBrightnessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BRIGHTNESS, pParent)
	, m_nBrightness(0)
{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRIGHTNESS_SLIDER, m_sliderBrightness);
	DDX_Text(pDX, IDC_BRIGHTNESS_EDIT, m_nBrightness);
	DDV_MinMaxInt(pDX, m_nBrightness, -255, 255);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_BRIGHTNESS_EDIT, &CBrightnessDlg::OnChangeBrightnessEdit)
END_MESSAGE_MAP()


// CBrightnessDlg 메시지 처리기


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderBrightness.SetRange(-255, 255);
	m_sliderBrightness.SetTicFreq(32);
	m_sliderBrightness.SetPageSize(32);
	m_sliderBrightness.SetPos(m_nBrightness);

	// 픽쳐 컨트롤의 크기를 구한다.
	CRect rect;
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_PREVIEW);
	pImageWnd->GetClientRect(rect);

	// 픽쳐 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절한다.
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppResizeNearest(imgSrc, imgDst, rect.Width(), rect.Height());
	IppImageToDib(imgDst, m_DibSrc);

	// 초기 임계값에 의한 미리보기 이진화 영상 만들기
	MakePreviewImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CBrightnessDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE_PREVIEW));
	m_DibRes.Draw(dcPreview.m_hDC, 0, 0);
}

void CBrightnessDlg::SetImage(IppDib& Dib)
{
	m_DibSrc = Dib;
	if (!m_DibSrc.IsValid())
	{
		AfxMessageBox(_T("비었음"));
	}
}

void CBrightnessDlg::MakePreviewImage()
{
	IppByteImage imgSrc;
	IppDibToImage(m_DibSrc, imgSrc);
	IppBrightness(imgSrc, m_nBrightness);
	IppImageToDib(imgSrc, m_DibRes);
}

void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderBrightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nBrightness = m_sliderBrightness.GetPos();
		UpdateData(FALSE);

		// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행한다.
		MakePreviewImage();
		Invalidate(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CBrightnessDlg::OnChangeBrightnessEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_sliderBrightness.SetPos(m_nBrightness);

	// 현재 설정된 임계값을 이용하여 미리보기 영상의 이진화를 수행한다.
	MakePreviewImage();
	Invalidate(FALSE);
}
