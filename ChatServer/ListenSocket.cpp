// ListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatServer.h"
#include "ListenSocket.h"
#include "ClientSocket.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode) // 서버가 접속을 기다리는 특정 포트로 클라이너트의 TCP 접속이 있을 때 자동으로 호출
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient)) // 새 클라이언트의 접속을 받아들인다.
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed to accept new client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
