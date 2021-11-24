// PictureControlDlg.cpp: 구현 파일
#include "pch.h"
#include "framework.h"
#include "PictureControl.h"
#include "PictureControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPictureControlDlg 대화 상자
CPictureControlDlg::CPictureControlDlg(CWnd* pParent)
			: CDialogEx(IDD_PICTURECONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPictureControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPictureControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMAGE_OPEN_BTN, &CPictureControlDlg::OnBnClickedImageOpenBtn)
END_MESSAGE_MAP()

// CPictureControlDlg 메시지 처리기
BOOL CPictureControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 그림 출력에 사용하기 위해 Picture Control의 위치를 얻는다.
	GetDlgItem(IDC_MY_PICTURE)->GetWindowRect(m_image_rect);
	// GetWindowRect로 좌표를 얻으면 캡션과 테두리 영역이 포함되기
	// 때문에 해당 영역을 제외시킨다.
	ScreenToClient(m_image_rect);

	return TRUE;
}

void CPictureControlDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic()){
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		if (!m_image.IsNull()) { // 그림이 로딩되었는지 체크한다.
			// 이미지가 원본 크기와 다르게 출력될때 어떤 방식으로 이미지를
			// 확대하거나 축소할 것인지를 결정한다.
			dc.SetStretchBltMode(COLORONCOLOR); 
			// 그림을 Picture Control 크기로 화면에 출력한다.
			m_image.Draw(dc, m_image_rect);
		}
	}
}

HCURSOR CPictureControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPictureControlDlg::OnBnClickedImageOpenBtn()
{
	if (m_image.IsNull()) {  // 이미 그림이 읽혀졌는지 체크한다.
		m_image.Load(L"yjin.bmp"); // 'yjin.bmp' 파일을 읽어서 비트맵 객체를 구성한다.
		// Picture Control 위치의 화면을 갱신해서 그림을 보이게 한다.
		InvalidateRect(m_image_rect, FALSE); 
	}
}
