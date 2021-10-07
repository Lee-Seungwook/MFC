
// ChattingClientDlg.h: 헤더 파일
//

#pragma once
#include "ClientSocket.h"


// CChattingClientDlg 대화 상자
class CChattingClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CChattingClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CClientSocket m_Client;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATTINGCLIENT_DIALOG };
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
	CListBox m_List;
//	CEdit m_Edit;
//	CButton m_ButtonSend;
//	CButton m_ButtonConnect;
//	afx_msg void OnClickedButtonConnect();
//	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonConnect();
	CButton m_ButtonConnect;
	CButton m_ButtonSend;
	afx_msg void OnClickedButtonSend();
	CString m_strData;
};
