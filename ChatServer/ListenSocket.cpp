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
	CClientSocket* pClient = new CClientSocket; // 객체에 접속한 클라이언트의 정보가 저장
	if (Accept(*pClient)) // 새 클라이언트의 접속을 받아들인다.
	{
		pClient->SetListenSocket(this); // ClientSocket클래스 객체가 목록에 접근할 수 있도록 ListenSocket클래스 객체의 주소를 설정
		m_ptrClientSocketList.AddTail(pClient); // 목록에 추가
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed to accept new client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient); // 목록을 검색한 후, 특정 클라이언트를 저장
	if (pos != NULL)
	{
		if (pClient != NULL) // 특정 클라이언트를 찾으면
		{
			pClient->ShutDown(); // 통신을 중지
			pClient->Close(); // 소켓을 닫아 연결을 종료
		}

		m_ptrClientSocketList.RemoveAt(pos); // 리스트에서 삭제되고
		delete pClient; // 객체 삭제
	}
}


void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2); // 첫 번째 인자로 전달받은 주소가 가리키는 메모리의 내용을 네트워크로 전송
																// 두 번째 인자는 전송할 메모리의 크기, 유니코드를 사용하므로 문자열 길이에 2를 곱한다.
		}
	}
}
