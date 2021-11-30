
// VisionImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "VisionImage.h"
#include "VisionImageDlg.h"
#include "afxdialogex.h"

#include "IppImage.h"
#include "IppConvert.h"
#include "ImageSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisionImageDlg 대화 상자



CVisionImageDlg::CVisionImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISIONIMAGE_DIALOG, pParent)
	, m_nEditHeight(0)
	, m_nEditWidth(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	width = 0;
	height = 0;
	m_bMagFlag = FALSE;
	m_bMoveFlag = FALSE;
	m_bSaveFlag = FALSE;
	ImageCorX = 0;
	ImageCorY = 0;
	PrintW = 0;
	PrintH = 0;
	nThumbImgWidth = 0;
	nThumbImgHeight = 0;
}

void CVisionImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_WIDTH, m_SliderWidth);
	DDX_Control(pDX, IDC_SLIDER_HEIGHT, m_SliderHeight);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nEditHeight);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nEditWidth);
	DDX_Control(pDX, IDC_IMAGE, m_Picture);
	DDX_Control(pDX, IDC_SMALL_IMAGE, m_Thumbnail);
}

BEGIN_MESSAGE_MAP(CVisionImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CVisionImageDlg::OnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CVisionImageDlg::OnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_MAG, &CVisionImageDlg::OnClickedButtonMag)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CVisionImageDlg::OnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CVisionImageDlg::OnChangeEditWidth)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CVisionImageDlg 메시지 처리기

BOOL CVisionImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	// 픽처 컨트롤의 크기를 구함
	CWnd* pImageWnd = GetDlgItem(IDC_IMAGE);
	pImageWnd->GetClientRect(m_Image_rect);
	
	CWnd* pSmallImageWnd = GetDlgItem(IDC_SMALL_IMAGE);
	pSmallImageWnd->GetClientRect(m_SmallPic);

	// 픽처 컨트롤의 좌표를 구함

	GetDlgItem(IDC_IMAGE)->GetWindowRect(&m_Image_rect);
	ScreenToClient(&m_Image_rect);

	GetDlgItem(IDC_SMALL_IMAGE)->GetWindowRect(&m_SmallPic);
	ScreenToClient(&m_SmallPic);
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CVisionImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CVisionImageDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	/*CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	CPen* oldPen = dc.SelectObject(&pen);
	
	dc.Rectangle(m_pRectTl.x, m_pRectTl.y, m_pRectBr.x, m_pRectBr.y);*/

	// 픽처 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE));
	CPaintDC dcSmall(GetDlgItem(IDC_SMALL_IMAGE));

	if (m_bMagFlag == FALSE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, nThumbImgWidth, nThumbImgHeight);
	}
	else if (m_bMagFlag == TRUE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, m_Position.Width(), m_Position.Height(),
			ImageCorX, ImageCorY, m_Position.Width() / 4, m_Position.Height() / 4);

		m_DibRes.Draw(dcSmall.m_hDC, 0, 0, m_SmallPic.Width(), m_SmallPic.Height());
	}
	

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CVisionImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVisionImageDlg::SetImage(IppDib& dib)
{
	m_DibSrc = dib;

	float fRatio = 1.0f;

	int nPreviewHeight = m_Image_rect.Height() - 5;
	int nPreviewWidth = m_Image_rect.Width() - 5;
	
	nOriginImgHeight = m_DibSrc.GetHeight();
	nOriginImgWidth = m_DibSrc.GetWidth();

	fRatio = min((float)nPreviewWidth / (float)nOriginImgWidth, (float)nPreviewHeight / (float)nOriginImgHeight);
	
	if (fRatio < 1)
	{
		//썸네일이 픽처컨트롤 보다 크다면 픽처컨트롤의 크기만큼 축소한다. 축소는 썸네일 이미지의 비율을 유지하도록 한다.
		nThumbImgWidth = static_cast<int>(nOriginImgWidth * fRatio);
		nThumbImgHeight = static_cast<int>(nOriginImgHeight * fRatio);
	}
	else
	{
		//썸네일이 픽처컨트롤의 크기보다 작다면 원본 썸네일 이미지 크기를 그대로 출력한다
		nThumbImgWidth = (int)(nOriginImgWidth*0.99);
		nThumbImgHeight = (int)(nOriginImgHeight*0.99);
	}

	if (m_DibSrc.GetBitCount() == 8)
	{
		IppByteImage imgSrc, imgDst;
		IppDibToImage(m_DibSrc, imgSrc);
		IppResizeBilinear(imgSrc, imgDst, nThumbImgWidth, nThumbImgHeight);
		IppImageToDib(imgDst, m_DibRes);

		Invalidate(TRUE);
	}
	else
	{
		AfxMessageBox(_T("잘못된 형식입니다."));
	}
}

void CVisionImageDlg::SetFlag()
{

}

void CVisionImageDlg::OnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szFilter = _T("Image(*.BMP, *.JPG) | *.BMP;*.JPG | ALL Files(*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		m_Dib.Load(CT2A(strPathName));
		
		if (m_Dib.IsValid())
		{
			m_DibSave = m_Dib;
			if (m_Dib.GetBitCount() == 8)
			{
				
			}
			else if (m_Dib.GetBitCount() == 24)
			{
				IppRgbImage imgSrc;
				IppByteImage imgDst;

				IppDibToImage(m_Dib, imgSrc);
				imgDst.Convert(imgSrc);
				IppImageToDib(imgDst, m_Dib);
			}

			SetImage(m_Dib);
		}
		else
		{
			AfxMessageBox(_T("*.bmp, *.jpg 형식의 파일만 지원합니다."));
		}
	}
	
	m_Dib.DestroyBitmap(); // 이걸 안 하면 연속적인 이미지 띄우기가 안됨.
}


void CVisionImageDlg::OnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString szFilter = _T("Image(*.BMP) | *.BMP; | ALL Files(*.*)|*.*||");

	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		if (m_DibSave.IsValid())
		{
			m_DibSave.Save(CT2A(strPathName));
		}
		else
		{
			AfxMessageBox(_T("*.bmp 형식의 파일만 지원합니다."));
		}
	}
}

void CVisionImageDlg::OnClickedButtonMag()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_DibRes.IsValid())
	{
		m_bMagFlag = !m_bMagFlag;
		m_bSaveFlag = FALSE;
		Invalidate(TRUE);

		width = m_Image_rect.Width();
		height = m_Image_rect.Height();

		int RangeH, RangeW;
		int FreqH, FreqW;

		RangeH = height - m_Image_rect.Height() / 4;
		RangeW = width - m_Image_rect.Width() / 4;

		m_SliderHeight.SetRange(0, RangeH);
		m_SliderWidth.SetRange(0, RangeW);

		FreqH = height / 8;
		FreqW = width / 8;

		m_SliderHeight.SetTicFreq(FreqH);
		m_SliderWidth.SetTicFreq(FreqW);

		m_SliderHeight.SetPageSize(FreqH);
		m_SliderWidth.SetPageSize(FreqW);

		m_Thumbnail.GetWindowRect(&m_SmallPic);

		if (m_bMagFlag == FALSE)
		{
			m_SmallPic.SetRectEmpty();
		}
	}
	else
	{
		AfxMessageBox(_T("영상이 없습니다."));
	}
	
}

void CVisionImageDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_SliderHeight.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_SliderHeight.GetPos();
		ImageCorY = nPos;

		m_nEditHeight = ImageCorY;
		UpdateData(FALSE);
		Invalidate(FALSE);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CVisionImageDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_SliderWidth.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		int nPos = m_SliderWidth.GetPos();
		ImageCorX = nPos;

		m_nEditWidth = ImageCorX;
		UpdateData(FALSE);
		Invalidate(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVisionImageDlg::OnChangeEditHeight()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	m_SliderHeight.SetPos(m_nEditHeight);

	Invalidate(FALSE);
}


void CVisionImageDlg::OnChangeEditWidth()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_SliderWidth.SetPos(m_nEditWidth);

	Invalidate(FALSE);
}


// 이미지의 크기가 컨트롤의 크기보다 작으면 확대가 안됨...

//BOOL CVisionImageDlg::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	CBrush br;
//	br.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 255));
//	FillRect(pDC, &br);
//	return TRUE;;
//}
