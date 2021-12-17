#pragma once


// CHoughLineDlg 대화 상자

class CHoughLineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHoughLineDlg)

public:
	CHoughLineDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHoughLineDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOUGHLINE_CANNY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	float m_fSigmaH;
	CSliderCtrl m_sliderSigmaH;
	float m_fLowThH;
	CSliderCtrl m_sliderLowThH;
	float m_fMaxThH;
	CSliderCtrl m_sliderMaxThH;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeHgaussianEdit();
	afx_msg void OnEnChangeHlowEdit();
	afx_msg void OnEnChangeHmaxEdit();
};
