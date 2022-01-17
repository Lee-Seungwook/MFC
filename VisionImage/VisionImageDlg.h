
// VisionImageDlg.h: 헤더 파일
//

#pragma once
#include <atlimage.h>
#include "IppDib.h"
#include "IppImage.h"

#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"

#include "afxwin.h"



// CVisionImageDlg 대화 상자
class CVisionImageDlg : public CDialogEx
{
private:
	CRect m_Image_rect; // Picture Control의 위치를 기억할 변수
	CRect m_Position; // 이미지를 출력하는 변수
	CRect m_SmallPic; // 확대 시 부분 화면을 출력하기 위한 변수
	CImage m_Image; // 사용자가 선택한 이미지 객체를 구성할 변수
	
	BOOL m_bMagFlag; // 확대를 명령하는 플래그
	BOOL m_bMoveFlag; // 확대하여 움직임을 명령하는 플래그
	BOOL m_bSaveFlag; // 확대하여 움직였을 때의 좌표를 기억하기 위한 플래그
	BOOL m_bCursorOnImage; // 픽처 컨트롤 위에 마우스가 위치할때를 기억하기 위한 플래그
	BOOL m_bCurImgLoad; // 이미지 불러 왔을 때의 마우스 좌표를 출력하기 위한 플래그
	BOOL m_bCurImgMag; // 이미지 확대 했을 때의 마우스 좌표를 출력하기 위한 플래그
	BOOL m_bIOFlag; // 작업 이전, 이후 영상 전환 플래그
	CPoint m_pRectTl, m_pRectBr;

	CSliderCtrl m_SliderWidth;
	CSliderCtrl m_SliderHeight;

	CStatic m_Picture;
	CStatic m_Thumbnail;

	CImage m_img;

	CListBox m_ListBox;

	float fRatio; // 원본 영상의 축소 비율
	float SfRatioW, SfRatioH;
	float fPtRatio; // 마우스 좌표를 출력하기 위한 비율

	int Tempx;

	int width, height; // 영상의 초기 너비와 높이

	int ImageCorX, ImageCorY; // 확대 영상의 시작 좌표
	int SmallCorX, SmallCorY; // 축소 영상의 좌표

	int PrintW, PrintH; // 확대 영상의 움직인 좌표

	int nOriginImgWidth, nOriginImgHeight; // 원본 영상의 너비와 높이
	int nThumbImgWidth, nThumbImgHeight; // 출력 영상의 너비와 높이

	int m_nEditHeight;
	int m_nEditWidth;

	int m_nPixels;

	int m_nEndPosX, m_nEndPosY;
	int m_nStartPosX, m_nStartPosY;
	float m_fHorizontalRatio;

	BYTE **p; // 영상의 픽셀 정보

	HWND hWindow;
	int iBitmapFlag = 0;
	CBitmap capture_map;
	unsigned char *arrImage1;
	unsigned char *arrImage2;

// 생성입니다.
public:
	CVisionImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	IppDib m_DibSrc;
	IppDib m_DibRes;
	IppDib m_Dib;
	IppDib m_DibSave;
	IppDib dib;
	IppDib dibPrev;

	CTab1 pDlg1;
	CTab2 pDlg2;
	CTab3 pDlg3;

	// CTab1 *Tab1;

	CTabCtrl m_TabRecipe;

	CWnd* m_pwndShow;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISIONIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonOpen();
	afx_msg void OnClickedButtonSave();
	afx_msg void OnClickedButtonMag();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// afx_msg void OnLbnDblclkListFilter();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonInoutput();
	afx_msg void OnTcnSelchangeTabRecipe(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void SetImage(IppDib& dib); // 초기 이미지 설정하여 출력
	void DrawLine(); // 미리보기 출력 영역 사각형 그리기

	void DbcFilterGaussian(IppByteImage& imgWork); // 가우시안 필터 다이얼로그 활성
	void DbcInverse(IppByteImage& imgWork); // 영상 반전
	void DbcContrast(IppByteImage& imgWork); // 영상 명암비 조절
	void DbcBrightness(IppByteImage& imgWork); // 영상 밝기 조절
	void DbcGammaCorrection(IppByteImage& imgWork); // 영상 감마 조절
	void DbcLaplacian(IppByteImage& imgWork); // 라플라시안 필터
	void DbcUnsharpMask(IppByteImage& imgWork); // 언샤프마스크 필터
	void DbcHighboost(IppByteImage& imgWork); // 하이부스트 필터

	void DbcBinary(IppDib& dibWork); // 이진화
	void DbcRotate(IppDib& dibWork); // 회전 수행

	void DbcEdgeRoberts(IppByteImage& imgWork); // 엣지 로버츠
	void DbcEdgePrewitt(IppByteImage& imgWork); // 엣지 프리윗
	void DbcEdgeSobel(IppByteImage& imgWork); // 엣지 소벨
	void DbcEdgeCanny(IppByteImage& imgWork); // 엣지 캐니
	void DbcHoughLine(IppByteImage& imgWork); // 허프 직선

	void GetIndexF(int GetIndex); // Tab1의 리스트 박스 인덱스를 받기 위함
	void GetIndexI(int GetIndex); // Tab2의 리스트 박스 인덱스를 받기 위함
	void GetIndexD(int GetIndex); // Tab3의 리스트 박스 인덱스를 받기 위함

	void OnDestroy();
};
