#pragma once


// CCannyEdgeDlg 대화 상자

class CCannyEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCannyEdgeDlg)

public:
	CCannyEdgeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCannyEdgeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CANNYEDGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fSigma;
	CSliderCtrl m_sliderSigma;
	float m_fLowTh;
	CSliderCtrl m_sliderLowTh;
	float m_fMaxTh;
	CSliderCtrl m_sliderMaxTh;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeGaussianEdit();
	afx_msg void OnEnChangeLowEdit();
	afx_msg void OnEnChangeMaxEdit();
};
