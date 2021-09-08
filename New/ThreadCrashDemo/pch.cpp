// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

CCriticalSection g_CS;
TCHAR* g_pszBuffer = NULL;

void SetString(TCHAR* pszData)
{
	g_CS.Lock();
	int nLength = lstrlen(pszData) + 1; // 전달받은 문자열의 길이를 저장
	if (g_pszBuffer != NULL) free(g_pszBuffer); // 메모리 해제

	g_pszBuffer = (TCHAR*)malloc(sizeof(TCHAR) *  nLength); // 메모리 할당
	swprintf_s(g_pszBuffer, nLength, _T("%s"), pszData);
	g_CS.Unlock();
}

BOOL GetString(TCHAR* pszData)
{
	g_CS.Lock();
	if (pszData != NULL && g_pszBuffer != NULL) // 문자열이 있고, 버퍼에 주소가 있을때
	{
		int nLength = lstrlen(g_pszBuffer);
		swprintf_s(pszData, nLength + 1, _T("%s"), g_pszBuffer); // pszData에 g_pszBuffer를 저장...

		g_CS.Unlock();
		return TRUE;
	}

	g_CS.Unlock();
	return FALSE;
}

UINT ThreadFunc1(LPVOID pParam)
{
	while (TRUE)
	{
		::Sleep(1);
		SetString(_T("ThreadFunc1"));
	}

	return 0;
}

UINT ThreadFunc2(LPVOID pParam)
{
	while (TRUE)
	{
		::Sleep(1);
		SetString(_T("ThreadFunc2"));
	}

	return 0;
}
