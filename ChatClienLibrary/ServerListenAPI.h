#pragma once
#include <afxsock.h>
#include "..\ChattingServer\ChattingServer\ChattingServerDlg.h"
#include "..\ChattingServer\ChattingServer\ChildSocket.h"

#ifdef  _DLL_SERVER_
#define DLL_SERVER _declspec(dllexport)
#else
#define DLL_SERVER __declspec(dllimport)
#endif //  _DLL_SERVER_

class DLL_SERVER CServerListenAPI : public CAsyncSocket
{
public: 
	// void APIAccept( CPtrList &m_ptrChildSocketList);
	void APICloseClientSocket(CSocket* (&pChild), CPtrList &m_ptrChildSocketList);
	void APIBroadCast(char* pszBuffer, int len, CPtrList &m_ptrChildSocketList);
};



