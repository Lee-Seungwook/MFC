#include "pch.h"
#include "ChattingServer.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ChattingServerDlg.h"



void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CChildSocket* pChild = new CChildSocket;

	BOOL check = Accept(*pChild);

	if (check == FALSE) {
		delete pChild;
		AfxMessageBox(_T("접속허용실패"));
		return;
	}

	pChild->SetListenSocket(this);
	m_ptrChildSocketList.AddTail(pChild);

	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetApp()->GetMainWnd();

	pMain->m_List.AddString(_T("서버 접속 허용"));
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL) {
		pChild->ShutDown();
		pChild->Close();
	}
	m_ptrChildSocketList.RemoveAt(pos);
	delete pChild;
}


void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = NULL;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if (pChild != NULL)
			pChild->Send(pszBuffer, len * 2);
	}
}
