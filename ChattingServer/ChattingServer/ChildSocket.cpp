#include "pch.h"
#include "ChattingServer.h"
#include "ChattingServerDlg.h"
#include "ChildSocket.h"
#include "ListenSocket.h"


void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	m_pListenSocket = pSocket;
}


void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListenSocket* pServerSocket = (CListenSocket *)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
	CSocket::OnClose(nErrorCode);
}


void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString tmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	GetPeerName(strIPAddress, uPortNumber);

	int len;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();
		tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
		pMain->m_List.AddString(tmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
	}
	CSocket::OnReceive(nErrorCode);
}
