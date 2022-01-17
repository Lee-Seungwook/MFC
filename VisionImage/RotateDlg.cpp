// RotateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "VisionImage.h"
#include "RotateDlg.h"
#include "afxdialogex.h"

#include "IppImage.h"
#include "IppConvert.h"
#include "ImageSize.h"

// CRotateDlg 대화 상자

IMPLEMENT_DYNAMIC(CRotateDlg, CDialogEx)

CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROTATE, pParent)
	, m_nRotate(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROTATE_SLIDER, m_sliderRotate);
	DDX_Text(pDX, IDC_ROTATE_EDIT, m_nRotate);
	DDV_MinMaxInt(pDX, m_nRotate, 0, 359);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_ROTATE_EDIT, &CRotateDlg::OnChangeRotateEdit)
END_MESSAGE_MAP()


// CRotateDlg 메시지 처리기


BOOL CRotateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_sliderRotate.SetRange(0, 359);
	m_sliderRotate.SetTicFreq(32);
	m_sliderRotate.SetPageSize(32);
	m_sliderRotate.SetPos(m_nRotate);

	// 픽처 컨트롤의 크기를 구함
	CRect rect;
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE_PREVIEW);
	pImageWnd->GetClientRect(rect);

	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppResizeNearest(imgSrc, imgDst, rect.Width(), rect.Height());
	IppImageToDib(imgDst, m_DibSrc);

	// 초기 임계값에 의한 미리보기 이진화 영상 만들기
	MakePreviewImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRotateDlg::SetImage(IppDib& Dib)
{
	m_DibSrc = Dib;
	if (!m_DibSrc.IsValid())
	{
		AfxMessageBox(_T("비었음"));
	}
}

void CRotateDlg::MakePreviewImage()
{
	IppByteImage imgSrc, imgDst;
	IppDibToImage(m_DibSrc, imgSrc);
	IppRotate(imgSrc, imgDst, m_nRotate);
	IppImageToDib(imgDst, m_DibRes);
}

void CRotateDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE_PREVIEW));
	m_DibRes.Draw(dcPreview.m_hDC, 0, 0);
}


void CRotateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 슬라이드바에서 발생한 WM_HSCROLL 메시지인 경우 처리
	if (m_sliderRotate.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_sliderRotate.GetPos();
		m_nRotate = nPos;
		UpdateData(FALSE);

		// 현재 설정된 임계값을 이용하여 미리보기 영상의 회전을 수행
		MakePreviewImage();
		Invalidate(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CRotateDlg::OnChangeRotateEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// 에디트 컨트롤에서 글자가 바뀐 경우, 슬라이더 컨트롤의 위치를 조절
	UpdateData(TRUE);
	m_sliderRotate.SetPos(m_nRotate);

	// 현재 설정된 각도를 이용하여 미리보기 영상의 회전을 수행
	MakePreviewImage();
	Invalidate(FALSE);
}
