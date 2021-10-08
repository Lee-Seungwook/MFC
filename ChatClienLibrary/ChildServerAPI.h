#pragma once
#include <afxsock.h>
#include "..\ChattingServer\ChattingServer\ChattingServerDlg.h"
#include "..\ChattingServer\ChattingServer\ListenSocket.h"

#ifdef  _DLL_CHILD_
#define DLL_CHILD _declspec(dllexport)
#else
#define DLL_CHILD __declspec(dllimport)
#endif //  _DLL_CHILD_

class DLL_CHILD CChildServerAPI :
	public CSocket
{
public:
	void APIReceive(char *szBuffer, CString& tmp, CString& strIPAddress, int len);
};

