
// VisionImageDlg.h: 헤더 파일
//

#pragma once
#include <atlimage.h>
#include "IppDib.h"
#include "IppImage.h"

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
	CPoint m_pRectTl, m_pRectBr;
	float fRatio;

	int Tempx;

	int width, height; // 영상의 초기 너비와 높이

	int ImageCorX, ImageCorY; // 확대 영상의 시작 좌표
	int SmallCorX, SmallCorY; // 축소 영상의 좌표

	int PrintW, PrintH; // 확대 영상의 움직인 좌표

	int nOriginImgWidth, nOriginImgHeight; // 원본 영상의 너비와 높이
	int nThumbImgWidth, nThumbImgHeight; // 출력 영상의 너비와 높이

// 생성입니다.
public:
	CVisionImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	IppDib m_DibSrc;
	IppDib m_DibRes;
	IppDib m_Dib;
	IppDib m_DibSave;

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

public:
	void SetImage(IppDib& dib); // 초기 이미지 설정하여 출력
	void SetFlag(); // 아직 사용 X
	CSliderCtrl m_SliderWidth;
	CSliderCtrl m_SliderHeight;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_nEditHeight;
	int m_nEditWidth;
	afx_msg void OnChangeEditHeight();
	afx_msg void OnChangeEditWidth();
	CStatic m_Picture;
	CStatic m_Thumbnail;

	CImage m_img;
	int m_nEndPosX, m_nEndPosY;
	int m_nStartPosX, m_nStartPosY;
	float m_fHorizontalRatio;

	void OnDrawImage();
	void DrawLine(CDC* pDC);
	void DrawImage(CDC* pDC);


};
