
// VisionImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "VisionImage.h"
#include "VisionImageDlg.h"
#include "afxdialogex.h"
#include <algorithm>
#include <functional>
#include "vfw.h"
#include <iostream>

#include "AviChildFrame.h"
#include "AviDoc.h"
#include "AviView.h"

#include "IppImage.h"
#include "IppConvert.h"
#include "ImageSize.h"
#include "IppFilter.h"
#include "IppEnhance.h"
#include "IppSegment.h"
#include "IppFeature.h"

#include "GaussianDlg.h"
#include "BrightnessDlg.h"
#include "ContrastDlg.h"
#include "GammaCorrectionDlg.h"
#include "BinarizationDlg.h"
#include "CannyEdgeDlg.h"
#include "HoughLineDlg.h"
#include "RotateDlg.h"

#include "Tab1.h"

#include <gdiplus.h> //gdi+
#pragma comment(lib, "gdiplus.lib") //gdi+

#pragma comment (lib, "vfw32.lib")

using namespace Gdiplus;
using namespace std;
using namespace cv;

#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img) \
	IppByteImage img; \
	IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB(img, dib) \
	IppDib dib; \
	IppImageToDib(img, dib);

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
	afx_msg void OnEnChangeGaussianEdit();
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
	, m_nPixels(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	width = 0;
	height = 0;
	
	ImageCorX = 0;
	ImageCorY = 0;
	PrintW = 0;
	PrintH = 0;
	nThumbImgWidth = 0;
	nThumbImgHeight = 0;

	m_nStartPosX = 0;
	m_nStartPosY = 0;
	m_nEndPosX = 0;
	m_nEndPosY = 0;
	m_fHorizontalRatio = 0;

	SmallCorX = 0;
	SmallCorY = 0;

	Tempx = 0;

	fRatio = 1.0f;
	SfRatioW = 1.0f;
	SfRatioH = 1.0f;
	fPtRatio = 1.0f;
	
	m_bMagFlag = FALSE;
	m_bMoveFlag = FALSE;
	m_bSaveFlag = FALSE;
	m_bCursorOnImage = FALSE;
	m_bCurImgLoad = FALSE;
	m_bCurImgMag = FALSE;
	m_bIOFlag = FALSE;
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
	DDX_Text(pDX, IDC_EDIT_PIXELS, m_nPixels);
	DDX_Control(pDX, IDC_LIST_FILTER, m_ListBox);
	DDX_Control(pDX, IDC_TAB_RECIPE, m_TabRecipe);
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
	ON_WM_MOUSEMOVE()
	// ON_LBN_DBLCLK(IDC_LIST_FILTER, &CVisionImageDlg::OnLbnDblclkListFilter)
	ON_BN_CLICKED(IDC_BUTTON_INOUTPUT, &CVisionImageDlg::OnClickedButtonInoutput)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_RECIPE, &CVisionImageDlg::OnTcnSelchangeTabRecipe)
	ON_WM_ERASEBKGND()
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

	m_pRectTl = m_Image_rect.TopLeft();
	m_pRectBr = m_Image_rect.BottomRight();

	m_pSmallRectTl = m_SmallPic.TopLeft();
	m_pSmallRectBr = m_SmallPic.BottomRight();

	/*Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);*/

	this->m_TabRecipe.InsertItem(0, _T("F"));
	this->m_TabRecipe.InsertItem(1, _T("I"));
	this->m_TabRecipe.InsertItem(2, _T("D"));

	CRect rect;
	this->m_TabRecipe.GetClientRect(&rect);
	this->pDlg1.Create(IDD_TAB1, &this->m_TabRecipe);
	this->pDlg1.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

	this->pDlg2.Create(IDD_TAB2, &this->m_TabRecipe);
	this->pDlg2.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	this->pDlg3.Create(IDD_TAB3, &this->m_TabRecipe);
	this->pDlg3.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);

	//hWindow = capCreateCaptureWindow(NULL, WS_CHILD | WS_VISIBLE, 0, 0, 640, 480, m_hWnd, 1);

	//bool ret = capDriverConnect(hWindow, 0);
	//if (ret == false)
	//{
	//	AfxMessageBox(_T("Webcam not found"), MB_ICONERROR);

	//	return false;
	//}



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
	
	dc.Rectangle(m_pRectTl.x - 5, m_pRectTl.y - 5, m_pRectBr.x + 5, m_pRectBr.y + 5);*/

	// 픽처 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE));
	CPaintDC dcSmall(GetDlgItem(IDC_SMALL_IMAGE));

	if (m_bMagFlag == FALSE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, nThumbImgWidth, nThumbImgHeight);
	}
	else if (m_bMagFlag == TRUE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, nThumbImgWidth, nThumbImgHeight,
			ImageCorX, ImageCorY, nThumbImgWidth / 3, nThumbImgHeight / 3);

		m_DibRes.Draw(dcSmall.m_hDC, 0, 0, m_SmallPic.Width(), m_SmallPic.Height());

		int ThumbRect_Width = m_SmallPic.Width() / 3;
		int ThumbRect_Height = m_SmallPic.Height() / 3;

		CPen pen;
		pen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		CPen* oldPen = dcSmall.SelectObject(&pen);
		dcSmall.MoveTo(SmallCorX, SmallCorY);
		dcSmall.LineTo(SmallCorX + ThumbRect_Width, SmallCorY);
		dcSmall.LineTo(SmallCorX + ThumbRect_Width, SmallCorY + ThumbRect_Height);
		dcSmall.LineTo(SmallCorX, SmallCorY + ThumbRect_Height);
		dcSmall.LineTo(SmallCorX, SmallCorY);

		dcSmall.SelectObject(oldPen);
		pen.DeleteObject();
	}
	// ::ReleaseDC(m_hWnd, dcPreview);


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

	int nPreviewHeight = m_Image_rect.Height();
	int nPreviewWidth = m_Image_rect.Width();
	
	nOriginImgHeight = m_DibSrc.GetHeight();
	nOriginImgWidth = m_DibSrc.GetWidth();

	fRatio = min((float)nPreviewWidth / (float)nOriginImgWidth, (float)nPreviewHeight / (float)nOriginImgHeight);
	fPtRatio = min((float)nOriginImgWidth / (float)nPreviewWidth, (float)nOriginImgHeight / (float)nPreviewHeight);

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
		IppByteImage imgSrc, imgTmp, imgDst;
		IppDibToImage(m_DibSrc, imgSrc);
		IppFilterWeightedMean(imgSrc, imgTmp);
		// IppResizeBilinear(imgSrc, imgDst, nThumbImgWidth, nThumbImgHeight);
		IppResizeCubic(imgTmp, imgDst, nThumbImgWidth, nThumbImgHeight);
		IppImageToDib(imgDst, m_DibRes);

		p = imgSrc.GetPixels2D();

		/*CRect r;
		r = { m_pRectTl.x, m_pRectTl.y, m_pRectBr.x + 10, m_pRectBr.y + 10 };

		InvalidateRect(&r, TRUE);*/
		Invalidate(TRUE);
		cout << "영상 출력" << endl;
		cout << endl;
	}
	else
	{
		AfxMessageBox(_T("잘못된 형식입니다."));
	}
}

void CVisionImageDlg::DbcFilterGaussian(IppByteImage& imgWork)
{
	CGaussianDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc = imgWork;
		IppFloatImage imgDst;
		IppFilterGaussian(imgSrc, imgDst, dlg.m_fSigma);
		IppImageToDib(imgDst, dib);
		
		cout << "가우시안 필터 적용" << endl;
		cout << endl;

		SetImage(dib);
		
		m_ListBox.AddString(_T("Filter_Gaussian"));
	}
}

void CVisionImageDlg::DbcInverse(IppByteImage& imgWork)
{
	IppByteImage imgSrc = imgWork;
	IppInverse(imgSrc);
	IppImageToDib(imgSrc, dib);

	cout << "영상 반전 적용" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Inverse"));
}

void CVisionImageDlg::DbcBrightness(IppDib& DibWork)
{
	CBrightnessDlg dlg;
	IppDib Dib = DibWork;

	dlg.SetImage(Dib);
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc;
		IppDibToImage(Dib, imgSrc);
		IppBrightness(imgSrc, dlg.m_nBrightness);
		IppImageToDib(imgSrc, dib);

		cout << "영상 밝기 적용" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Brightness"));
	}
}

void CVisionImageDlg::DbcContrast(IppDib& DibWork)
{
	CContrastDlg dlg;
	IppDib Dib = DibWork;

	dlg.SetImage(Dib);
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc;
		IppDibToImage(Dib, imgSrc);
		IppContrast(imgSrc, dlg.m_nContrast);
		IppImageToDib(imgSrc, dib);

		cout << "영상 명암비 적용" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Contrast"));
	}
}

void CVisionImageDlg::DbcGammaCorrection(IppDib& DibWork)
{
	CGammaCorrectionDlg dlg;
	IppDib Dib = DibWork;

	dlg.SetImage(Dib);
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc;
		IppDibToImage(Dib, imgSrc);
		IppGammaCorrection(imgSrc, dlg.m_fGamma);
		IppImageToDib(imgSrc, dib);

		cout << "영상 감마 조절 적용" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Gamma_Correction"));
	}
}

void CVisionImageDlg::DbcLaplacian(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	IppFilterLaplacian(imgSrc, imgDst);
	IppImageToDib(imgDst, dib);

	cout << "라플라시안 필터 적용" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Filter_Laplacian"));
}

void CVisionImageDlg::DbcUnsharpMask(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	IppFilterUnsharpMask(imgSrc, imgDst);
	IppImageToDib(imgDst, dib);

	cout << "언샤프 마스크 필터 적용" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Filter_UnsharpMask"));
}

void CVisionImageDlg::DbcHighboost(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	float alpha = 1.2f;
	IppFilterHighboost(imgSrc, imgDst, alpha);
	IppImageToDib(imgDst, dib);

	cout << "하이부스트 필터 적용" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Filter_Highboost"));
}

void CVisionImageDlg::DbcBinary(IppDib& DibWork)
{
	IppDib Dib = DibWork;
	CBinarizationDlg dlg;
	dlg.SetImage(Dib);

	IppByteImage imgSrc;
	IppDibToImage(Dib, imgSrc);

	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgDst;
		IppBinarization(imgSrc, imgDst, dlg.m_nThreshold);
		IppImageToDib(imgDst, dib);

		cout << "영상의 이진화 적용" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Binary"));
	}
}

void CVisionImageDlg::DbcRotate(IppDib& DibWork)
{
	CRotateDlg dlg;
	IppDib Dib = DibWork;

	dlg.SetImage(Dib);
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc, imgDst;
		IppDibToImage(Dib, imgSrc);
		IppRotate(imgSrc, imgDst, dlg.m_nRotate);
		IppImageToDib(imgDst, dib);

		cout << "영상의 회전 적용" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Rotate"));
	}
}

void CVisionImageDlg::DbcEdgeRoberts(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	IppEdgeRoberts(imgSrc, imgDst);
	IppImageToDib(imgDst, dib);

	cout << "로버츠 엣지 검출" << endl;
	cout << endl;

	SetImage(dib);
	
	m_ListBox.AddString(_T("Edgg_Roberts"));
}

void CVisionImageDlg::DbcEdgePrewitt(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	IppEdgePrewitt(imgSrc, imgDst);
	IppImageToDib(imgDst, dib);

	cout << "프리윗 엣지 검출" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Edge_Prewitt"));
}

void CVisionImageDlg::DbcEdgeSobel(IppByteImage& imgWork)
{
	IppByteImage imgSrc, imgDst;
	imgSrc = imgWork;
	IppEdgeSobel(imgSrc, imgDst);
	IppImageToDib(imgDst, dib);

	cout << "소벨 엣지 검출" << endl;
	cout << endl;

	SetImage(dib);

	m_ListBox.AddString(_T("Edge_Sobel"));
}

void CVisionImageDlg::DbcEdgeCanny(IppByteImage& imgWork)
{
	CCannyEdgeDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		/*IppByteImage imgSrc = imgWork;
		IppByteImage imgDst;
		IppEdgeCanny(imgSrc, imgDst, dlg.m_fSigma, dlg.m_fLowTh, dlg.m_fMaxTh);
		IppImageToDib(imgDst, dib);*/
		IppByteImage imgSrc = imgWork;

		Mat mat;
		IppImageToMat(imgSrc, mat);

		Mat matEdge;
		double lowTh = dlg.m_fLowTh, highTh = dlg.m_fMaxTh;
		Canny(mat, matEdge, dlg.m_fLowTh, dlg.m_fMaxTh, 3);

		IppByteImage imgEdge;
		IppMatToImage(matEdge, imgEdge);
		IppImageToDib(imgEdge, dib);

		cout << "캐니 엣지 검출" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Edge_Canny"));
	}
}

void CVisionImageDlg::DbcHoughLine(IppByteImage& imgWork)
{
	CHoughLineDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		IppByteImage imgSrc = imgWork;
		IppByteImage imgEdge;
		IppEdgeCanny(imgSrc, imgEdge, dlg.m_fSigmaH, dlg.m_fLowThH, dlg.m_fMaxThH);

		vector<IppLineParam> lines;
		IppHoughLine(imgEdge, lines);

		if (lines.size() == 0)
		{
			AfxMessageBox(_T("검출된 직선이 없습니다."));
			return;
		}

		sort(lines.begin(), lines.end()); // vector 정렬

		// 최대 10개의 직선만 그려줌 (수정을 통해 그려질 직선의 개수를 조정할 수 있다.)
		int cnt = __min(10, lines.size());
		for (int i = 0; i < cnt; i++)
			IppDrawLine(imgSrc, lines[i], 255);

		IppImageToDib(imgSrc, dib);

		cout << "허프 직선 검출" << endl;
		cout << endl;

		SetImage(dib);

		m_ListBox.AddString(_T("Hough_Line"));
	}
}

void CVisionImageDlg::OnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szFilter = _T("Image(*.BMP, *.JPG) | *.BMP;*.JPG; | ALL Files(*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		
		m_Dib.Load(CT2A(strPathName)); // 큰 이미지 영상 설정 IppDib 사용

		//m_img.Load(strPathName); // 작은 이미지 영상 설정 CImage 사용

		// m_fHorizontalRatio = (float)m_SmallPic.Width() / m_img.GetWidth();

		

		if (m_Dib.IsValid())
		{
			m_DibSave = m_Dib;

			m_bCurImgLoad = TRUE;

			if (m_Dib.GetBitCount() == 8)
			{
				dib = m_Dib;
				
				cout << "영상 불러옴" << endl;
				cout << endl;
			}
			else if (m_Dib.GetBitCount() == 24)
			{
				IppRgbImage imgSrc;
				IppByteImage imgDst;

				IppDibToImage(m_Dib, imgSrc);
				imgDst.Convert(imgSrc);
				IppImageToDib(imgDst, m_Dib);

				dib = m_Dib;

				cout << "영상 불러옴" << endl;
				cout << endl;
			}

			SetImage(m_Dib);
			GetDlgItem(IDC_LIST_FILTER)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_MAG)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_INOUTPUT)->EnableWindow(TRUE);
			GetDlgItem(IDC_TAB_RECIPE)->EnableWindow(TRUE);

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

			cout << "영상 저장" << endl;
			cout << endl;
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
		m_bCurImgMag = !m_bCurImgMag;
		
		ImageCorX = 0;
		ImageCorY = (nThumbImgHeight * 2 / 3);

		SmallCorX = 0;
		SmallCorY = 0; // m_SmallPic.Height() / 3;
		
		PrintW = m_SmallPic.Width() / 3;
		PrintH = m_SmallPic.Height() / 3;

		width = nThumbImgWidth;
		height = nThumbImgHeight;

		int RangeH, RangeW;
		int FreqH, FreqW;

		RangeH = height - nThumbImgHeight / 3;
		RangeW = width - nThumbImgWidth / 3;

		m_SliderHeight.SetRange(0, RangeH);
		m_SliderWidth.SetRange(0, RangeW);

		FreqH = height / 8;
		FreqW = width / 8;

		m_SliderHeight.SetTicFreq(FreqH);
		m_SliderWidth.SetTicFreq(FreqW);

		m_SliderHeight.SetPageSize(FreqH);
		m_SliderWidth.SetPageSize(FreqW);

		m_Thumbnail.GetWindowRect(&m_SmallPic);

		SfRatioW = (float)(m_SmallPic.Width() - m_SmallPic.Width() / 3) / RangeW;
		SfRatioH = (float)(m_SmallPic.Height() - m_SmallPic.Height() / 3) / RangeH;

		cout << "영상 확대" << endl;
		cout << endl;

		/*CRect r;
		r = { m_pSmallRectTl.x, m_pSmallRectTl.y, m_pSmallRectBr.x + 10, m_pSmallRectBr.y + 10 };

		InvalidateRect(&r, TRUE);*/

		Invalidate(TRUE);
		
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
		ImageCorY = (nThumbImgHeight * 2 / 3) - nPos; // 혹은 요거나 
		// m_nEditHeight = ImageCorY;

		int tempY = nThumbImgHeight - nPos;

		SmallCorY = m_SmallPic.Height() - static_cast<int>((float)tempY * SfRatioH); // 요게 문제인듯

		UpdateData(FALSE);
		
		CRect r;
		r = { m_pSmallRectTl.x, m_pSmallRectTl.y, m_pSmallRectBr.x + 10, m_pSmallRectBr.y + 10 };

		InvalidateRect(&r, FALSE);

		r = NULL;
		r = { m_pRectTl.x, m_pRectTl.y, m_pRectBr.x + 10, m_pRectBr.y + 10 };

		InvalidateRect(&r, FALSE);

		// Invalidate(TRUE);
		
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
		// m_nEditWidth = ImageCorX;

		SmallCorX = static_cast<int>((float)ImageCorX * SfRatioW);

		UpdateData(FALSE);

		CRect r;
		r = { m_pSmallRectTl.x, m_pSmallRectTl.y, m_pSmallRectBr.x + 10, m_pSmallRectBr.y + 10 };

		InvalidateRect(&r, FALSE);

		r = NULL;
		r = { m_pRectTl.x, m_pRectTl.y, m_pRectBr.x + 10, m_pRectBr.y + 10 };

		InvalidateRect(&r, FALSE);

		// Invalidate(TRUE);
		
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//void CVisionImageDlg::DrawLine()
//{
//	/*CPen *pOldPen, pen;
//	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//
//	pOldPen = pDC->SelectObject(&pen);
//
//	pDC->MoveTo(m_nStartPosX, m_nStartPosY);
//	pDC->LineTo(m_nEndPosX, m_nStartPosY);
//	pDC->LineTo(m_nEndPosX, m_nEndPosY);
//	pDC->LineTo(m_nStartPosX, m_nEndPosY);
//
//	pDC->SelectObject(pOldPen);
//
//	pen.DeleteObject();*/
//	CClientDC dc(GetDlgItem(IDC_SMALL_IMAGE));
//
//	Graphics g(dc);
//
//	Pen pen(Color(255, 255, 0, 0), 3);
//
//	 g.DrawLine(&pen, SmallCorX, SmallCorY, SmallCorX + PrintW, SmallCorY);
//	 g.DrawLine(&pen, SmallCorX + PrintW, SmallCorY, SmallCorX + PrintW, SmallCorY - PrintH);
//	 g.DrawLine(&pen, SmallCorX + PrintW, SmallCorY - PrintH, SmallCorX, SmallCorY - PrintH);
//	 g.DrawLine(&pen, SmallCorX, SmallCorY - PrintH, SmallCorX, SmallCorY);
//
//	 Invalidate(FALSE);
//}

void CVisionImageDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;

	((CStatic*)GetDlgItem(IDC_IMAGE))->GetWindowRect(&rt);
	ScreenToClient(&rt);

	int m_ptX = 0;
	int	m_ptY = 0;
	if (m_bCurImgLoad == TRUE)
	{
		if (m_bCurImgMag == FALSE)
		{
			if (rt.PtInRect(point))
			{ 
				m_ptX = point.x * fPtRatio; // 좌표 구현은 했으나, 비율을 곱하는 것 때문에 3씩 더해지는 좌표로 출력....
				m_ptY = point.y * fPtRatio;

				m_nEditWidth = m_ptX;
				m_nEditHeight = m_ptY;
				// m_nPixels = p[m_ptX][m_ptY]; - 메모리 오류

				UpdateData(FALSE);
			}
			else
			{

			}
		}
		else if (m_bCurImgMag == TRUE)
		{
			if (rt.PtInRect(point)) // 비슷하게는 나옴...
			{
				float fPtMagRatio = fPtRatio / 3;
				m_ptX = point.x * fPtMagRatio + ImageCorX * fPtRatio; // 좌표 구현은 했으나, 비율을 곱하는 것 때문에 3씩 더해지는 좌표로 출력....
				m_ptY = point.y * fPtMagRatio + (nThumbImgHeight * 2 / 3) * fPtRatio - ImageCorY * fPtRatio;

				m_nEditWidth = m_ptX;
				m_nEditHeight = m_ptY;
				// m_nPixels = p[m_ptX][m_ptY]; - 메모리 오류

				UpdateData(FALSE);
			}
			else
			{

			}
		}
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}


//void CVisionImageDlg::OnLbnDblclkListFilter()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	int index = m_ListBox.GetCurSel();
//	
//	dibPrev = dib;
//	IppDib DibSrc = dib;
//	IppDib DibWork;
//	IppByteImage imgWork, imgRes, imgTmp;
//
//	if (DibSrc.GetBitCount() == 24)
//	{
//		IppRgbImage imgSrc;
//		IppByteImage imgDst;
//
//		IppDibToImage(DibSrc, imgSrc);
//		imgDst.Convert(imgSrc);
//		IppImageToDib(imgDst, DibWork);
//	}
//	else if (DibSrc.GetBitCount() == 8)
//	{
//		DibWork = DibSrc;
//	}
//	else
//	{
//		AfxMessageBox(_T("잘못된 파일 형식입니다."));
//	}
//
//	IppDibToImage(DibWork, imgWork);
//
//	switch (index)
//	{
//	case 0:
//		DbcFilterGaussian(imgWork);
//		break;
//
//	case 1:
//		DbcInverse(imgWork);
//		break;
//
//	case 2:
//		DbcBrightness(imgWork);
//		break;
//
//	case 3:
//		DbcContrast(imgWork);
//		break;
//
//	case 4:
//		DbcGammaCorrection(imgWork);
//		break;
//
//	case 5:
//		DbcLaplacian(imgWork);
//		break;
//
//	case 6:
//		DbcUnsharpMask(imgWork);
//		break;
//
//	case 7:
//		DbcHighboost(imgWork);
//		break;
//
//	default:
//		break;
//	}
//}


void CVisionImageDlg::OnClickedButtonInoutput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bIOFlag == FALSE)
		SetImage(dibPrev);
	else if (m_bIOFlag == TRUE)
		SetImage(dib);

	m_bIOFlag = !m_bIOFlag;

	cout << "영상 이전 / 이후" << endl;
	cout << endl;

}

void CVisionImageDlg::OnTcnSelchangeTabRecipe(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (this->m_pwndShow != NULL)
	{
		this->m_pwndShow->ShowWindow(SW_HIDE);
		this->m_pwndShow = NULL;
	}

	int iSelect = this->m_TabRecipe.GetCurSel();

		switch (iSelect)
		{
		case 0:
			this->pDlg1.ShowWindow(SW_SHOW);
			this->pDlg2.ShowWindow(SW_HIDE);
			this->pDlg3.ShowWindow(SW_HIDE);
			this->m_pwndShow = &this->pDlg1;
			break;

		case 1:
			this->pDlg1.ShowWindow(SW_HIDE);
			this->pDlg2.ShowWindow(SW_SHOW);
			this->pDlg3.ShowWindow(SW_HIDE);
			this->m_pwndShow = &this->pDlg2;
			break;

		case 2:
			this->pDlg1.ShowWindow(SW_HIDE);
			this->pDlg2.ShowWindow(SW_HIDE);
			this->pDlg3.ShowWindow(SW_SHOW);
			this->m_pwndShow = &this->pDlg3;
			break;
		}
	
	*pResult = 0;
}

void CVisionImageDlg::GetIndexF(int GetIndex)
{
	int index = GetIndex;

	dibPrev = dib;
	IppDib DibSrc = dib;
	IppDib DibWork;
	IppByteImage imgWork, imgRes, imgTmp;

	if (DibSrc.GetBitCount() == 24)
	{
		IppRgbImage imgSrc;
		IppByteImage imgDst;

		IppDibToImage(DibSrc, imgSrc);
		imgDst.Convert(imgSrc);
		IppImageToDib(imgDst, DibWork);
	}
	else if (DibSrc.GetBitCount() == 8)
	{
		DibWork = DibSrc;
	}
	else
	{
		AfxMessageBox(_T("잘못된 파일 형식입니다."));
	}

	IppDibToImage(DibWork, imgWork);

	switch (index)
	{
	case 0:
		DbcFilterGaussian(imgWork);
		break;

	case 1:
		DbcInverse(imgWork);
		break;

	case 2:
		DbcBrightness(DibWork);
		break;

	case 3:
		DbcContrast(DibWork);
		break;

	case 4:
		DbcGammaCorrection(DibWork);
		break;

	case 5:
		DbcLaplacian(imgWork);
		break;

	case 6:
		DbcUnsharpMask(imgWork);
		break;

	case 7:
		DbcHighboost(imgWork);
		break;

	default:
		break;
	}
}

void CVisionImageDlg::GetIndexI(int GetIndex)
{
	int index = GetIndex;

	dibPrev = dib;
	IppDib DibSrc = dib;
	IppDib DibWork;
	IppByteImage imgWork, imgRes, imgTmp;

	if (DibSrc.GetBitCount() == 24)
	{
		IppRgbImage imgSrc;
		IppByteImage imgDst;

		IppDibToImage(DibSrc, imgSrc);
		imgDst.Convert(imgSrc);
		IppImageToDib(imgDst, DibWork);
	}
	else if (DibSrc.GetBitCount() == 8)
	{
		DibWork = DibSrc;
	}
	else
	{
		AfxMessageBox(_T("잘못된 파일 형식입니다."));
	}

	IppDibToImage(DibWork, imgWork);

	switch (index)
	{
	case 0:
		DbcBinary(DibWork);
		break;

	case 1:
		DbcRotate(DibWork);
		break;

	default:
		break;
	}
}

void CVisionImageDlg::GetIndexD(int GetIndex)
{
	int index = GetIndex;

	dibPrev = dib;
	IppDib DibSrc = dib;
	IppDib DibWork;
	IppByteImage imgWork, imgRes, imgTmp;

	if (DibSrc.GetBitCount() == 24)
	{
		IppRgbImage imgSrc;
		IppByteImage imgDst;

		IppDibToImage(DibSrc, imgSrc);
		imgDst.Convert(imgSrc);
		IppImageToDib(imgDst, DibWork);
	}
	else if (DibSrc.GetBitCount() == 8)
	{
		DibWork = DibSrc;
	}
	else
	{
		AfxMessageBox(_T("잘못된 파일 형식입니다."));
	}

	IppDibToImage(DibWork, imgWork);

	switch (index)
	{
	case 0:
		DbcEdgeRoberts(imgWork);
		break;

	case 1:
		DbcEdgePrewitt(imgWork);
		break;

	case 2:
		DbcEdgeSobel(imgWork);
		break;
		
	case 3:
		DbcEdgeCanny(imgWork);
		break;

	case 4:
		DbcHoughLine(imgWork);
		break;

	default:
		break;
	}
}



BOOL CVisionImageDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	return CDialogEx::OnEraseBkgnd(pDC);
}
