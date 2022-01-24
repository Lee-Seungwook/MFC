
// VisionImageDlg.h: 헤더 파일
//

#pragma once
#include <atlimage.h>
#include "IppDib.h"
#include "IppImage.h"

#include "opencv2/opencv.hpp"

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
	CPoint m_pRectTl, m_pRectBr; // 본 영상의 좌표
	CPoint m_pSmallRectTl, m_pSmallRectBr; // 확대 미리보기 영상의 좌표

	CSliderCtrl m_SliderWidth; // HScroll
	CSliderCtrl m_SliderHeight; // VScroll

	CStatic m_Picture; // 본 영상 출력
	CStatic m_Thumbnail; // 미리보기 영상 출력

	CListBox m_ListBox; // 활성 레시피 출력 리스트
	CListBox m_ListFile; // 파일 출력 리스트

	CString mTopPath; // 최상위 작업 폴더
	std::vector<cv::Mat> mVecImage; // 영상 저장 벡터

	float fRatio; // 원본 영상의 축소 비율
	float SfRatioW, SfRatioH;
	float fPtRatio; // 마우스 좌표를 출력하기 위한 비율

	int width, height; // 영상의 초기 너비와 높이

	int ImageCorX, ImageCorY; // 확대 영상의 시작 좌표
	int SmallCorX, SmallCorY; // 축소 영상의 좌표

	int PrintW, PrintH; // 확대 영상의 움직인 좌표

	int nOriginImgWidth, nOriginImgHeight; // 원본 영상의 너비와 높이
	int nThumbImgWidth, nThumbImgHeight; // 출력 영상의 너비와 높이

	int m_nEditHeight; // 픽셀 y 좌표
	int m_nEditWidth; // 픽셀 x 좌표

	int m_nPixels; // 픽셀 수치 값

	int m_nStartPosX, m_nStartPosY; // 출력 영상 시작 좌표 

	int index; // 벡터 인덱스 콘솔 출력

	BYTE **p; // 영상의 픽셀 정보 -> 데이터 오류로 값 출력이 안됨....

	HWND hWindow;


// 생성입니다.
public:
	CVisionImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	IppDib m_DibSrc; // 입력 영상
	IppDib m_DibRes; // 입력 영상 크기 변환 결과
	IppDib m_DibSave; // 입력 영상 저장 영상
	IppDib dib; // 영상 전달을 위해 필요
	IppDib dibPrev; // 이전 영상 저장

	CTab1 pDlg1; // F Tab
	CTab2 pDlg2; // I Tab
	CTab3 pDlg3; // D Tab

	// CTab1 *Tab1;

	CTabCtrl m_TabRecipe; // 레시피 탭 컨트롤

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
	afx_msg void OnClickedButtonOpen(); // 파일 열기
	afx_msg void OnClickedButtonSave(); // 원본 영상으로 저장
	afx_msg void OnClickedButtonMag(); // 영상 확대
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); // 수직 이동
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); // 수평 이동
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); // 픽셀 좌표 출력
	afx_msg void OnClickedButtonInoutput(); // 현재, 이전 영상 출력
	afx_msg void OnTcnSelchangeTabRecipe(NMHDR *pNMHDR, LRESULT *pResult); // 레시피 탭

public:
	void SetImage(IppDib& dib); // 초기 이미지 설정하여 출력

	void typeImageRead(CString inputType); // 리스트 컨트롤 목록 생성 및 mVecImage에 영상 저장
	void SetIndexFile(int index); // index에 해당하는 mVecImage 영상 설정 

	void DbcFilterGaussian(IppByteImage& imgWork); // 가우시안 필터 다이얼로그 활성
	void DbcInverse(IppByteImage& imgWork); // 영상 반전
	void DbcContrast(IppDib& DibWork); // 영상 명암비 조절
	void DbcBrightness(IppDib& DibWork); // 영상 밝기 조절
	void DbcGammaCorrection(IppDib& DibWork); // 영상 감마 조절
	void DbcLaplacian(IppByteImage& imgWork); // 라플라시안 필터
	void DbcUnsharpMask(IppByteImage& imgWork); // 언샤프마스크 필터
	void DbcHighboost(IppByteImage& imgWork); // 하이부스트 필터

	void DbcBinary(IppDib& DibWork); // 이진화
	void DbcRotate(IppDib& DibWork); // 회전 수행

	void DbcEdgeRoberts(IppByteImage& imgWork); // 엣지 로버츠
	void DbcEdgePrewitt(IppByteImage& imgWork); // 엣지 프리윗
	void DbcEdgeSobel(IppByteImage& imgWork); // 엣지 소벨
	void DbcEdgeCanny(IppByteImage& imgWork); // 엣지 캐니
	void DbcHoughLine(IppByteImage& imgWork); // 허프 직선

	void DbcTemplateMatch(IppByteImage& imgWork); // openCV 템플릿 매칭 사용 (구현 아직 안함)

	void GetIndexF(int GetIndex); // Tab1의 리스트 박스 인덱스를 받기 위함
	void GetIndexI(int GetIndex); // Tab2의 리스트 박스 인덱스를 받기 위함
	void GetIndexD(int GetIndex); // Tab3의 리스트 박스 인덱스를 받기 위함

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDblclkListFile();
};
