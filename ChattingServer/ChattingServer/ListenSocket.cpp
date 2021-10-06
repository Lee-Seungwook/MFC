#include "pch.h"
#include "ChattingServer.h"
#include "ListenSocket.h"
#include "ChildSocket.h"
#include "ChattingServerDlg.h"



void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CChildSocket* pChild = new CChildSocket;

	BOOL check = Accept(*pChild);

	if (check == FALSE) {
		delete pChild;
		AfxMessageBox(_T("����������"));
		return;
	}

	pChild->SetListenSocket(this);
	m_ptrChildSocketList.AddTail(pChild);

	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetMainWnd();

	pMain->m_List.AddString(_T("���� ���� ���"));
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
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