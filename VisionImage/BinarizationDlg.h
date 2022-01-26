﻿#pragma once
#include "IppDib.h"
#include "IppImage.h"

// CBinarizationDlg 대화 상자

class CBinarizationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBinarizationDlg)

public:
	CBinarizationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBinarizationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARIZATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nThreshold;
	CSliderCtrl m_SliderThreshold;

	IppDib m_DibSrc;
	IppDib m_DibRes;

	void SetImage(IppDib& dib);
	void MakePreviewImage();

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnChangeThresholdEdit();
	afx_msg void OnBnClickedOk();
};
