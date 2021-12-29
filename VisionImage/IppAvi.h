#pragma once

#include <Vfw.h>
#include "IppDib.h"

class IppAvi
{
public:
	// ������
	IppAvi();
	~IppAvi();

public:
	// ��� �Լ�
	BOOL Open(LPCTSTR lpszPathName); // ������ ����, ���� ��Ʈ�����κ��� ������� ���� ���� �������� �غ�
	void Close(); // ������ ����� ����

	// �׸��� �Լ�
	void DrawFrame(HDC hDC, int nFrame);
	void DrawFrame(HDC hDC, int nFrame, int dx, int dy);
	void DrawFrame(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);

	// ���� ������ ĸ�� �Լ� (IppDib Ŭ���� Ÿ������ ��ȯ)
	BOOL GetFrame(int nFrame, IppDib& dib);

	// AVI ���� ���� ��ȯ �Լ�
	int GetFrameRate() { return m_nFrameRate; } // �ʴ� ������ ���� ��ȯ
	int GetTotalFrame() { return m_nTotalFrame; } // ��ü ������ ���� ��ȯ
	int GetHeight() { return m_nHeight; } // ���� �ȼ� ũ�⸦ ��ȯ
	int GetWidth() { return m_nWidth; } // ���� �ȼ� ũ�⸦ ��ȯ
	BOOL IsValid() { return (m_pAviFile != NULL); }; // ������ ��ȿ���� �˻�

protected:
	// ��� ����
	PAVIFILE m_pAviFile;         // AVI ���� �������̽� ������
	PAVISTREAM m_pVideoStream;     // ���� ��Ʈ�� ������
	PGETFRAME m_pVideoFrame;      // ���� ������ ������

	int m_nWidth;           // ���� ������(����) ���� ũ��
	int m_nHeight;          // ���� ������(����) ���� ũ��

	int m_nTotalFrame;      // ��ü ������ ����
	int m_nFrameRate;       // �ʴ� ������ ����
};

