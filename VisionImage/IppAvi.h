#pragma once

#include <Vfw.h>
#include "IppDib.h"

class IppAvi
{
public:
	// 생성자
	IppAvi();
	~IppAvi();

public:
	// 멤버 함수
	BOOL Open(LPCTSTR lpszPathName); // 파일을 열고, 비디오 스트림으로부터 압축되지 않은 비디오 프레임을 준비
	void Close(); // 파일의 사용을 중지

	// 그리기 함수
	void DrawFrame(HDC hDC, int nFrame);
	void DrawFrame(HDC hDC, int nFrame, int dx, int dy);
	void DrawFrame(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);

	// 현재 프레임 캡쳐 함수 (IppDib 클래스 타입으로 변환)
	BOOL GetFrame(int nFrame, IppDib& dib);

	// AVI 파일 정보 반환 함수
	int GetFrameRate() { return m_nFrameRate; } // 초당 프레임 수를 반환
	int GetTotalFrame() { return m_nTotalFrame; } // 전체 프레임 수를 반환
	int GetHeight() { return m_nHeight; } // 세로 픽셀 크기를 반환
	int GetWidth() { return m_nWidth; } // 가로 픽셀 크기를 반환
	BOOL IsValid() { return (m_pAviFile != NULL); }; // 비디오가 유효한지 검사

protected:
	// 멤버 변수
	PAVIFILE m_pAviFile;         // AVI 파일 인터페이스 포인터
	PAVISTREAM m_pVideoStream;     // 비디오 스트림 포인터
	PGETFRAME m_pVideoFrame;      // 비디오 프레임 포인터

	int m_nWidth;           // 비디오 프레임(영상) 가로 크기
	int m_nHeight;          // 비디오 프레임(영상) 가로 크기

	int m_nTotalFrame;      // 전체 프레임 개수
	int m_nFrameRate;       // 초당 프레임 비율
};

