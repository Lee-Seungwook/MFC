#pragma once


// CContrastDlg 대화 상자

class CContrastDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContrastDlg)

public:
	CContrastDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CContrastDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTRAST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	IppDib m_DibSrc; // 입력 영상의 축소 복사본
	IppDib m_DibRes; // 회전을 적용한 영상

	CSliderCtrl m_sliderContrast;
	int m_nContrast;

public:
	void SetImage(IppDib& dib);
	void MakePreviewImage();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeContrastEdit();
	
};
