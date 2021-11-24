
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
	CImage m_Image; // 사용자가 선택한 이미지 객체를 구성할 변수
	int width, height;

// 생성입니다.
public:
	CVisionImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	IppDib m_DibSrc;
	IppDib m_DibRes;
	IppDib m_Dib;

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

public:
	void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
	void SetImage(IppDib& dib);
};
