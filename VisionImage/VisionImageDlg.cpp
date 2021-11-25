
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	width = 0;
	height = 0;
	m_bMagFlag = FALSE;
	m_bMoveFlag = FALSE;
	m_bSaveFlag = FALSE;
	ImageCorX = 0;
	ImageCorY = 0;
}

void CVisionImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVisionImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CVisionImageDlg::OnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CVisionImageDlg::OnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_MAG, &CVisionImageDlg::OnClickedButtonMag)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	width = m_Image_rect.Width();
	height = m_Image_rect.Height();

	// 픽처 컨트롤의 좌표를 구함
	GetDlgItem(IDC_IMAGE)->GetWindowRect(&m_Image_rect);
	ScreenToClient(&m_Image_rect);

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
	if (m_bMagFlag == FALSE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, m_Image_rect.Width(), m_Image_rect.Height()); 
	}
	else if (m_bMagFlag == TRUE)
	{
		m_DibRes.Draw(dcPreview.m_hDC, 0, 0, m_Image_rect.Width(), m_Image_rect.Height(), 
			ImageCorX, ImageCorY, m_Image_rect.Width() / 3, m_Image_rect.Height() / 3); 
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

	if (m_DibSrc.GetBitCount() == 8)
	{
		IppByteImage imgSrc, imgDst;
		IppDibToImage(m_DibSrc, imgSrc);
		IppResizeBilinear(imgSrc, imgDst, m_Image_rect.Width(), m_Image_rect.Height());
		IppImageToDib(imgDst, m_DibRes);
		Invalidate(FALSE);
	}
	else if (m_DibSrc.GetBitCount() == 24)
	{
		IppRgbImage imgTemp;
		IppByteImage imgSrc, imgDst;
		IppDibToImage(m_DibSrc, imgTemp);
		imgSrc.Convert(imgTemp);
		IppResizeBilinear(imgSrc, imgDst, m_Image_rect.Width(), m_Image_rect.Height());
		IppImageToDib(imgDst, m_DibRes);
		Invalidate(FALSE);
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
		if (m_DibRes.IsValid())
		{
			m_DibRes.Save(CT2A(strPathName));
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
		Invalidate(FALSE);
	}
	else
	{
		AfxMessageBox(_T("영상이 없습니다."));
	}
	
}


void CVisionImageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x > m_Image_rect.left && point.x < m_Image_rect.right
		&& point.y > m_Image_rect.top && point.y < m_Image_rect.bottom && m_bMagFlag)
	{
		m_bMoveFlag = TRUE;
		m_pMousePt.x = point.x;
		m_pMousePt.y = point.y;
		Invalidate(FALSE);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CVisionImageDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bMoveFlag)
	{
		m_bMoveFlag = !m_bMoveFlag;
		m_bSaveFlag = TRUE;

	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CVisionImageDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bMoveFlag)
	{
		if (!m_bSaveFlag)
		{
			int x, y;
			x = point.x - m_pMousePt.x;
			y = point.y - m_pMousePt.y;

			if (x > 0)
				SaveX = ImageCorX = x / 2;
			
			if (y > 0)
				SaveY = ImageCorY = y / 2;

			Invalidate(FALSE);
		}
		else if (m_bSaveFlag)
		{
			int x, y;
			x = point.x - SaveX;
			y = point.y - SaveY;

			if (x > 0)
				SaveX = ImageCorX = x / 2;

			if (y > 0)
				SaveY = ImageCorY = y / 2;

			Invalidate(FALSE);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
