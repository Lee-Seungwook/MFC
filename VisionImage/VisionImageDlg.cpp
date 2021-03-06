
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
#include "opencv2/opencv.hpp"

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

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

#include <gdiplus.h> //gdi+
#pragma comment(lib, "gdiplus.lib") //gdi+

using namespace Gdiplus;
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
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
	, m_bPixels(0)
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

	SmallCorX = 0;
	SmallCorY = 0;

	fRatio = 1.0f;
	SfRatioW = 1.0f;
	SfRatioH = 1.0f;
	fPtRatio = 1.0f;

	index = 0;
	
	m_bMagFlag = FALSE;
	m_bMoveFlag = FALSE;
	m_bSaveFlag = FALSE;
	m_bCursorOnImage = FALSE;
	m_bCurImgLoad = FALSE;
	m_bCurImgMag = FALSE;
	m_bIOFlag = FALSE;
}

CVisionImageDlg::~CVisionImageDlg()
{
	m_DibSrc.DestroyBitmap();
	m_DibRes.DestroyBitmap();
	m_DibSave.DestroyBitmap();
	dib.DestroyBitmap();
	dibPrev.DestroyBitmap();
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
	//  DDX_Text(pDX, IDC_EDIT_PIXELS, m_nPixels);
	DDX_Control(pDX, IDC_LIST_FILTER, m_ListBox);
	DDX_Control(pDX, IDC_TAB_RECIPE, m_TabRecipe);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListFile);
	DDX_Text(pDX, IDC_EDIT_PIXELS, m_bPixels);
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
	ON_LBN_DBLCLK(IDC_LIST_FILE, &CVisionImageDlg::OnDblclkListFile)
	ON_WM_DESTROY()
//	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CVisionImageDlg::OnEnChangeEditWidth)
END_MESSAGE_MAP()


// CVisionImageDlg 메시지 처리기

BOOL CVisionImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_CrtSetBreakAlloc(7061);

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

	

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


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

	// 픽처 컨트롤의 크기에 맞게 입력 영상의 복사본의 크기를 조절
	CPaintDC dcPreview(GetDlgItem(IDC_IMAGE));
	CPaintDC dcSmall(GetDlgItem(IDC_SMALL_IMAGE));

	if (m_bMagFlag == FALSE)
	{
		// m_DibRes.Draw(dcPreview.m_hDC, 0, 0, nThumbImgWidth, nThumbImgHeight);
		m_DibRes.Draw(dcPreview.m_hDC, m_nStartPosX, m_nStartPosY, nThumbImgWidth, nThumbImgHeight);
	}
	else if (m_bMagFlag == TRUE)
	{
		if (nThumbImgWidth > nOriginImgWidth || nThumbImgHeight > nOriginImgHeight)
		{
			m_DibRes.Draw(dcPreview.m_hDC, m_nStartPosX, m_nStartPosY, nOriginImgWidth, nOriginImgHeight);
		}
		else if (nThumbImgWidth < nOriginImgWidth || nThumbImgHeight < nOriginImgHeight)
		{
			m_DibRes.Draw(dcPreview.m_hDC, m_nStartPosX, m_nStartPosY, nThumbImgWidth, nThumbImgHeight,
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
		else
		{
			AfxMessageBox(_T("영상 확인 필요"));
			cout << "Image Draw Error onPaint()" << endl;
			printf("\n");
		}
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
	// fPtRatio = min((float)nOriginImgWidth / (float)nPreviewWidth, (float)nOriginImgHeight / (float)nPreviewHeight);
	// fPtRatio를 이용하여 작은 영상 크기 설정 시 밑의 조건문에 부합하는 것이 없어 너비와 높이가 0인 영상을 만들어 동적할당을 함
	// 이때, 동적할당을 해제하는데, 메모리 접근 오류로 인해 디버그 오류가 생기는 것으로 보인다.

	if (fRatio < 1)
	{
		//썸네일이 픽처컨트롤 보다 크다면 픽처컨트롤의 크기만큼 축소한다. 축소는 썸네일 이미지의 비율을 유지하도록 한다.
		nThumbImgWidth = static_cast<int>(nOriginImgWidth * fRatio);
		nThumbImgHeight = static_cast<int>(nOriginImgHeight * fRatio);
	}
	else if (fRatio >= 1)
	{
		//썸네일이 픽처컨트롤의 크기보다 작다면 원본 썸네일 이미지 크기를 그대로 출력한다
		nThumbImgWidth = static_cast<int>(nOriginImgWidth* fRatio);
		nThumbImgHeight = static_cast<int>(nOriginImgHeight* fRatio);
	}

	if (m_DibSrc.GetBitCount() == 8)
	{
		IppByteImage imgSrc, imgTmp, imgDst;
		IppDibToImage(m_DibSrc, imgSrc);
		IppFilterWeightedMean(imgSrc, imgTmp);
		IppResizeCubic(imgTmp, imgDst, nThumbImgWidth, nThumbImgHeight);
		IppImageToDib(imgDst, m_DibRes);

		// p = imgSrc.GetPixels2D();

		m_nStartPosX = (nPreviewWidth - nThumbImgWidth) / 2;
		m_nStartPosY = (nPreviewHeight - nThumbImgHeight) / 2;

		Invalidate(TRUE);
		cout << "영상 출력" << endl;
		printf("\n");
	}
	else
	{
		AfxMessageBox(_T("잘못된 형식입니다."));
	}
}

void CVisionImageDlg::typeImageRead(CString inputType)
{
	CString tpath = mTopPath; // 전역 변수 경로를 저장
	CString Folderpath; // 상위 폴더 + 확장자 경로를 저장

	// 실행 파일 경로에서 파일 명을 제외한 상위 폴더의 경로를 얻음
	int nLen = tpath.ReverseFind('\\');
	if (nLen > 0)
		tpath = tpath.Left(nLen);

	// 폴더에서 확장자 파일의 경로를 저장
	Folderpath = tpath + _T("\\*") + inputType;

	CFileFind finder; // 파일 탐색 클래스 선언
	BOOL bWorking = finder.FindFile(Folderpath); // 경로를 대입 (파일이 없는 경우 0을 반환)
	CString fileName; // 파일명을 저장할 변수

	while (bWorking) // 파일이 없을때까지 반복
	{
		bWorking = finder.FindNextFile(); // 다음 파일을 찾을 수 있게 함
		if (finder.IsArchived())
		{
			CString _fileName = finder.GetFileName(); // 확장자를 포함한 파일명을 가져옴
			if (_fileName == _T(".") ||
				_fileName == _T("..") ||
				_fileName == _T("Thumbs.db")) continue;
			fileName = finder.GetFileTitle(); // 확장자를 제외한 파일명을 저장
			
			fileName += inputType; // 확장자 문자열 대입
			m_ListFile.AddString(fileName); // 리스트 컨트롤에 파일명 삽입
			fileName = tpath + _T("\\") + fileName; // 영상 파일의 경로를 저장
			CT2CA pszConver(fileName); // CT2CA 는 unicode version const char* 를 ansi version const char* 로 변경해 주는 것
			
			std::string tmpImagePath(pszConver); // string 클래스에 파일 경로 저장
			cv::Mat img = cv::imread(tmpImagePath); // Mat 형식의 파일로 영상 불러옴

			if (img.empty())
			{
				cout << "Image load failed!" << endl;
				printf("\n");
				AfxMessageBox(_T("파일을 불러오지 못했습니다."));
				break;
			}
			else if (!img.empty())
			{
				GetDlgItem(IDC_LIST_FILTER)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_MAG)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_INOUTPUT)->EnableWindow(TRUE);
				GetDlgItem(IDC_TAB_RECIPE)->EnableWindow(TRUE);
				GetDlgItem(IDC_LIST_FILE)->EnableWindow(TRUE);
			}

			mVecImage.push_back(img); // 벡터에 영상 파일 저장
			
			if (!img.empty())
			{
				index++;
				cout << index << " 번 vector에 저장 " << endl;
				printf("\n");
			}
		}
	}
}

void CVisionImageDlg::SetIndexFile(int index)
{
	int m_Vindex = index;
	cv::Mat m_Vecimg;
	IppRgbImage m_DRgbimg;
	IppByteImage m_DByteimg;
	IppDib m_Dib;

	m_Vecimg = mVecImage.at(m_Vindex);

	IppMatToImage(m_Vecimg, m_DRgbimg);
	m_DByteimg.Convert(m_DRgbimg);
	IppImageToDib(m_DByteimg, m_Dib);

	if (m_Dib.IsValid())
	{
		m_bCurImgLoad = TRUE;

		if (m_Dib.GetBitCount() == 8)
		{
			dib = m_Dib;
			
			cout << "영상 불러옴" << endl;
			printf("\n");
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
			printf("\n");
		}
		SetImage(m_Dib);
		m_DibSave = m_Dib;
	}
	m_Dib.DestroyBitmap(); // 이걸 안 하면 연속적인 이미지 띄우기가 안됨.
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
		printf("\n");

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
	printf("\n");

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
		printf("\n");

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
		printf("\n");

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
		printf("\n");

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
	printf("\n");

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
	printf("\n");

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
	printf("\n");

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
		printf("\n");

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
		printf("\n");

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
	printf("\n");

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
	printf("\n");

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
	printf("\n");

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
		printf("\n");

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
		printf("\n");

		SetImage(dib);

		m_ListBox.AddString(_T("Hough_Line"));
		
	}
}

void CVisionImageDlg::OnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ListFile.ResetContent(); // 파일 목록 리스트 초기화
	mVecImage.clear(); // 벡터 초기화 크기 및 인자 0으로 초기화

	CString szFilter = _T("Image(*.BMP, *.JPG) | *.BMP;*.JPG; ||"); // ALL Files(*.*)|*.*|

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter); // 파일 선택 다이얼로그 

	if (IDOK == dlg.DoModal()) 
	{
		CString strPathName = dlg.GetPathName(); // 선택 파일 경로 얻어옴
		mTopPath = strPathName; // 전역 변수에 경로 저장
		CString ImageType = _T(".jpg"); // 확장자 문자열 저장
		typeImageRead(ImageType); // 파일 목록 저장 함수 호출

		ImageType = _T(".bmp"); // 확장자 문자열 저장
		typeImageRead(ImageType); // 파일 목록 저장 함수 호출

		ImageType = _T(".png"); // 확장자 문자열 저장
		typeImageRead(ImageType); // 파일 목록 저장 함수 호출
	}
	
	// BROWSEINFO를 활용하여 영상 목록을 리스트에 추가하고, 벡터에 영상을 대입 (폴더 내의 파일들을 확인할 수 없는 단점 있음)
	/*ITEMIDLIST *pidlBrowse;
	TCHAR       pszPathname[MAX_PATH];
	BROWSEINFO  BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select Directory");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, pszPathname);
	}

	mTopPath = (LPCTSTR)pszPathname;*/


	// 기존 파일 찾기 다이얼로그를 사용하여 하나의 영상만 띄우는 기능
	//IppDib m_Dib;
	//CString szFilter = _T("Image(*.BMP, *.JPG) | *.BMP;*.JPG; ||"); // ALL Files(*.*)|*.*|

	//CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	//if (IDOK == dlg.DoModal())
	//{
	//	CString strPathName = dlg.GetPathName();

	//	m_Dib.Load(CT2A(strPathName)); // 큰 이미지 영상 설정 IppDib 사용

	//	if (m_Dib.IsValid())
	//	{
	//		m_DibSave = m_Dib;

	//		m_bCurImgLoad = TRUE;

	//		if (m_Dib.GetBitCount() == 8)
	//		{
	//			dib = m_Dib;
	//			
	//			cout << "영상 불러옴" << endl;
	//			printf("\n");
	//		}
	//		else if (m_Dib.GetBitCount() == 24)
	//		{
	//			IppRgbImage imgSrc;
	//			IppByteImage imgDst;

	//			IppDibToImage(m_Dib, imgSrc);
	//			imgDst.Convert(imgSrc);
	//			IppImageToDib(imgDst, m_Dib);

	//			dib = m_Dib;

	//			cout << "영상 불러옴" << endl;
	//			printf("\n");
	//		}

	//		SetImage(m_Dib);
	//		GetDlgItem(IDC_LIST_FILTER)->EnableWindow(TRUE);
	//		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
	//		GetDlgItem(IDC_BUTTON_MAG)->EnableWindow(TRUE);
	//		GetDlgItem(IDC_BUTTON_INOUTPUT)->EnableWindow(TRUE);
	//		GetDlgItem(IDC_TAB_RECIPE)->EnableWindow(TRUE);

	//	}
	//	else
	//	{
	//		AfxMessageBox(_T("*.bmp, *.jpg 형식의 파일만 지원합니다."));
	//	}
	//}
	//
	//m_Dib.DestroyBitmap(); // 이걸 안 하면 연속적인 이미지 띄우기가 안됨.
}

void CVisionImageDlg::OnDblclkListFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_ListFile.GetCurSel();
	SetIndexFile(index);
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
			Mat m_MatSave;
			IppByteImage m_ByteSave;
			strPathName += _T(".bmp");
			CT2CA pszConver(strPathName);

			std::string tmpImagePath(pszConver);

			IppDibToImage(m_DibSave, m_ByteSave);
			IppImageToMat(m_ByteSave, m_MatSave);

			cv::imwrite(tmpImagePath, m_MatSave);

			// m_DibSave.Save(CT2A(strPathName));

			cout << "영상 저장" << endl;
			printf("\n");
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

		if (m_bMagFlag == FALSE)
		{
			m_SmallPic.SetRectEmpty();

			GetDlgItem(IDC_SLIDER_HEIGHT)->ShowWindow(FALSE);
			GetDlgItem(IDC_SLIDER_WIDTH)->ShowWindow(FALSE);
		}
		else if (m_bMagFlag == TRUE)
		{
			if (fRatio < 1)
			{
				GetDlgItem(IDC_SLIDER_HEIGHT)->ShowWindow(TRUE);
				GetDlgItem(IDC_SLIDER_WIDTH)->ShowWindow(TRUE);
			}

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

			UpdateData(TRUE);

			m_SliderHeight.SetPos(0);
			m_SliderWidth.SetPos(0);

			m_Thumbnail.GetWindowRect(&m_SmallPic);

			SfRatioW = (float)(m_SmallPic.Width() - m_SmallPic.Width() / 3) / RangeW;
			SfRatioH = (float)(m_SmallPic.Height() - m_SmallPic.Height() / 3) / RangeH;
		}

		cout << "영상 확대" << endl;
		printf("\n");

		/*CRect r;
		r = { m_pSmallRectTl.x, m_pSmallRectTl.y, m_pSmallRectBr.x + 10, m_pSmallRectBr.y + 10 };

		InvalidateRect(&r, TRUE);*/

		Invalidate(TRUE);
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
		ImageCorY = (nThumbImgHeight * 2 / 3) - nPos; 

		int tempY = nThumbImgHeight - nPos;

		SmallCorY = m_SmallPic.Height() - static_cast<int>((float)tempY * SfRatioH); 

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
	CRect rt(m_nStartPosX, m_nStartPosY, nOriginImgWidth, nOriginImgHeight);

	((CStatic*)GetDlgItem(IDC_IMAGE))->GetWindowRect(&rt);
	ScreenToClient(&rt);

	int m_ptX = 0;
	int	m_ptY = 0;

	IppByteImage ByteImgMouse;

	if (m_bCurImgLoad == TRUE)
	{
		IppDibToImage(m_DibRes, ByteImgMouse); // 컨트롤에 출력한 영상을 Image로 변환
		BYTE **p = ByteImgMouse.GetPixels2D(); // BYTE 형태의 Image 파일이므로 BYTE형 2차원 배열로 받는다.

		if (m_bCurImgMag == FALSE)
		{
			if (rt.PtInRect(point))
			{
				m_ptX = point.x - rt.left - m_nStartPosX; // 상수는 클라이언트에서 컨트롤까지의 거리
				m_ptY = point.y - rt.top - m_nStartPosY;

				// 영상 영역을 벗어난 경우 예외 처리 ( Image 컨트롤 가로 또는 세로에 맞춰서 출력하므로 각각의 최대 지점에서 벗어나는 경우에는 0으로 초기화가 안됨 )
				if (m_ptX < 0 || m_ptY < 0 || m_ptX > nThumbImgWidth || m_ptY > nThumbImgHeight) {
					m_ptX = 0; m_ptY = 0;
				}
				
				// 컨트롤의 가로 세로 크기 저장
				int m_Image_Width = m_Image_rect.Width();
				int m_Image_Height = m_Image_rect.Height();

				float m_fPtRatio; // 좌표 출력 시의 비율
				
				// 영상 출력 시 가장 작은 값으로 비율을 정해주므로, 역으로 가장 큰 값을 비율로 정해야 근사치가 나옴
				m_fPtRatio = max((float)nOriginImgWidth / (float)m_Image_Width, (float)nOriginImgHeight / (float)m_Image_Height); 
				
				m_nEditWidth = static_cast<int>(m_ptX * m_fPtRatio); // x 좌표
				m_nEditHeight = static_cast<int>(m_ptY * m_fPtRatio); // y 좌표
				
				// 픽셀 값 출력 (좌표가 1보다 큰 경우, 원본 이미지의 크기 보다 1 작은 경우에만 출력) -> 이외의 경우에는 메모리 접근 오류 출력
				if (m_ptX >= 1 && m_ptY >= 1 && m_ptX < nThumbImgWidth - 1 && m_ptY < nThumbImgHeight) m_bPixels = p[m_ptY][m_ptX]; 
			}
			UpdateData(FALSE);
		}
		//else if (m_bCurImgMag == TRUE)
		//{
		//	if (rt.PtInRect(point)) // 비슷하게는 나옴...
		//	{
		//		float fPtMagRatio = fPtRatio / 3;
		//		m_ptX = point.x * fPtMagRatio + ImageCorX * fPtRatio; // 좌표 구현은 했으나, 비율을 곱하는 것 때문에 3씩 더해지는 좌표로 출력....
		//		m_ptY = point.y * fPtMagRatio + (nThumbImgHeight * 2 / 3) * fPtRatio - ImageCorY * fPtRatio;

		//		m_nEditWidth = m_ptX;
		//		m_nEditHeight = m_ptY;
		//		// m_nPixels = p[m_ptX][m_ptY]; - 메모리 오류

		//		UpdateData(FALSE);
		//	}
		//	else
		//	{

		//	}
		//}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


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





void CVisionImageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	_CrtDumpMemoryLeaks();
}


//void CVisionImageDlg::OnEnChangeEditWidth()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialogEx::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
