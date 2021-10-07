#pragma once
#include <afxsock.h>
class CClientSocket :
	public CSocket
{
public:
	CString tmp;
	CString temp;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

