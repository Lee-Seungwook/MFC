#include "pch.h"
#include "afxdialogex.h"


#ifndef  _DLL_SERVER_
#define _DLL_SERVER_
#endif // ! _DLL_SERVER_

#include "ServerListenAPI.h"

//void CServerListenAPI::APIAccept(CPtrList &m_ptrChildSocketList)
//{
//	CChildSocket* pChild = new CChildSocket;
//
//	BOOL check = Accept(*pChild);
//
//	if (check == FALSE) {
//		delete pChild;
//		AfxMessageBox(_T("����������"));
//		return;
//	}
//
//	pChild->SetListenSocket(this);
//	m_ptrChildSocketList.AddTail(pChild);
//
//	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetApp()->GetMainWnd();
//
//	pMain->m_List.AddString(_T("���� ���� ���"));
//	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
//}

void CServerListenAPI::APICloseClientSocket(CSocket* (&pChild), CPtrList &m_ptrChildSocketList)
{
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL) {
		pChild->ShutDown();
		pChild->Close();
	}
	m_ptrChildSocketList.RemoveAt(pos);
	delete pChild;
}

void CServerListenAPI::APIBroadCast(char* pszBuffer, int len, CPtrList &m_ptrChildSocketList)
{
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