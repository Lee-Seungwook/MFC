#include "pch.h"
#include "afxdialogex.h"


#ifndef _DLL_CHILD_
#define _DLL_CHILD_
#endif // !_DLL_SERVER_

#include "ChildServerAPI.h"

void CChildServerAPI::APIReceive(char *szBuffer, CString& tmp, CString& strIPAddress, int len)
{
	CChattingServerDlg* pMain = (CChattingServerDlg*)AfxGetApp()->GetMainWnd();
	tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
	pMain->m_List.AddString(tmp);
	pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
}