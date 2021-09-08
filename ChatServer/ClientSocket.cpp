// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "ChatServerDlg.h"


// CClientSocket

CClientSocket::CClientSocket() 
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수





void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: 여기에 구현 코드 추가.
	m_pListenSocket = pSocket;
}


void CClientSocket::OnClose(int nErrorCode) // 연결이 종료되는 시점에 호출
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}


void CClientSocket::OnReceive(int nErrorCode) // 클라이언트로부터 정보를 수신해야 할때 호출됨, 채팅 메시지를 받았을때 호출
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CString strTmp = _T(""), strIPAdress = _T("");
	UINT uPortNumber = 0;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	GetPeerName(strIPAdress, uPortNumber); // 연결된 클라이언트의 정보를 알아낸다.
	if (Receive(szBuffer, sizeof(szBuffer)) > 0) // 메시지를 수신하고 받은 메시지를 연결된 모든 클라이언트에게 전송한다.
	{
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s : %d] : %s"), strIPAdress, uPortNumber, szBuffer);
		pMain->m_List.AddString(strTmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer); // 클라이언트에게 전송
	}
	CSocket::OnReceive(nErrorCode);
}
