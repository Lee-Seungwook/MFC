#include "pch.h"
#include "IppAvi.h"
#include "RGBBYTE.h"

IppAvi::IppAvi()
{
	// AVIFile ���̺귯���� �ʱ�ȭ�Ѵ�.
	AVIFileInit();

	// ��� �ʱ�ȭ
	m_pAviFile = NULL;
	m_pVideoStream = NULL;
	m_pVideoFrame = NULL;

	m_nWidth = 0;
	m_nHeight = 0;

	m_nTotalFrame = 0;
	m_nFrameRate = 0;
}

IppAvi::~IppAvi()
{
	Close();

	// AVIFile ���̺귯�� ����� �����Ѵ�.
	AVIFileExit();
}

/*************************************************************************
 *
 * �̸� : Open(LPCTSTR lpszFileName)
 * ���� : lpszFileName - �ҷ��� ������ ��ü ��� �̸�.
 * ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
 * ���� : AVI ������ IppAvi ��ü�� �ҷ��´�.
 *
 ************************************************************************/

BOOL IppAvi::Open(LPCTSTR lpszPathName)
{
	int i;
	HRESULT hr;

	AVIFILEINFO aviFileInfo;
	AVISTREAMINFO aviStreamInfo;
	PAVISTREAM pAviTmpStream = NULL;

	// ������ ������ open �� ���� ������ �ݴ´�.
	if (m_pAviFile)
	{
		Close();
		m_pAviFile = NULL;
	}

	// ������ ����, ���� �������̽��� ���� �����͸� m_pAvilFile�� ����
	hr = AVIFileOpen(&m_pAviFile, lpszPathName, OF_READ, NULL);
	if (hr)
		return FALSE;

	// ���Ͽ� ���� ������ ����
	hr = AVIFileInfo(m_pAviFile, &aviFileInfo, sizeof(AVIFILEINFO));
	if (hr)
	{
		Close();
		return FALSE;
	}

	for (i = 0; i < (LONG)aviFileInfo.dwStreams; i++)
	{
		// AVI ���ϰ� ���õ� ��Ʈ�� �������̽��� �ּҸ� ��´�.
		// fccType�� 0L ���� �����Ǹ� ��� ��Ʈ���� �˻�
		hr = AVIFileGetStream(m_pAviFile, &pAviTmpStream, 0L, i);
		if (hr)
			continue;

		// ������ ���� ��Ʈ�� �������̽��� ���� ������ ��´�.
		hr = AVIStreamInfo(pAviTmpStream, &aviStreamInfo, sizeof(AVISTREAMINFO));
		if (hr)
			continue;

		if (aviStreamInfo.fccType == streamtypeVIDEO)
		{
			m_pVideoStream = pAviTmpStream;

			// AVI ��Ʈ���� ��� ���� ������ ������Ŵ
			AVIStreamAddRef(m_pVideoStream);

			// ��ü ���� �� (VIDEO�� ��� ��ü ������ ��)
			m_nTotalFrame = aviStreamInfo.dwLength;

			// �ʴ� ���� �� (VIDEO�� ��� �ʴ� ������ ��)
			m_nFrameRate = aviStreamInfo.dwRate / aviStreamInfo.dwScale;

			// ���� ȭ���� ����, ���� ũ��
			RECT rc = aviStreamInfo.rcFrame;
			m_nWidth = rc.right - rc.left;
			m_nHeight = rc.bottom - rc.top;

			// ���� ��Ʈ�����κ��� ������� ���� ���� �������� �غ�
			m_pVideoFrame = AVIStreamGetFrameOpen(m_pVideoStream, NULL);
			if (!m_pVideoFrame)
			{
				Close();
				return FALSE;
			}
		}
		else
		{
			// Video ��Ʈ���� �ƴ� ��� ������� �ʰ� �״�� ��ȯ
			AVIStreamRelease(pAviTmpStream);
		}
	}
	return TRUE;
}

/*************************************************************************
 *
 * �̸� : Close()
 * ���� : ����.
 * ��ȯ : ����.
 * ���� : AVI ������ ����� �����Ѵ�.
 *
 ************************************************************************/

void IppAvi::Close()
{
	if (m_pVideoFrame != NULL)
	{
		AVIStreamGetFrameClose(m_pVideoFrame);
		m_pVideoFrame = NULL;
	}

	if (m_pVideoStream != NULL)
	{
		AVIStreamRelease(m_pVideoStream);
		m_pVideoStream = NULL;
	}

	if (m_pAviFile != NULL)
	{
		AVIFileRelease(m_pAviFile);
		m_pAviFile = NULL;
	}
}

/*************************************************************************
 *
 * �̸� : Draw(HDC hDC, int nFrame)
 * ���� : hDC    - ��� ��ġ�� DC �ڵ�
 *        nFrame - ����� ������ ��ȣ
 * ��ȯ : ����.
 * ���� : ��� ��ġ ��ǥ (0,0) ��ġ�� nFrame ��° �������� ����Ѵ�.
 *
 ************************************************************************/

void IppAvi::DrawFrame(HDC hDC, int nFrame)
{
	BYTE* pDib = (BYTE*)AVIStreamGetFrame(m_pVideoFrame, nFrame);
	if (!pDib)
		return;

	LPBITMAPINFO lpbi;
	LPSTR lpDIBBits;

	lpbi = (LPBITMAPINFO)pDib;

	if (lpbi->bmiHeader.biBitCount == 8)
		lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER) + 1024;
	else
		lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER);

	::SetDIBitsToDevice(hDC,	// hDC
		0,						// DestX
		0,						// DestY
		m_nWidth,				// nSrcWidth
		m_nHeight,				// nSrcHeight
		0,						// SrcX
		0,						// SrcY
		0,						// nStartScan
		(WORD)m_nHeight,		// nNumScans
		lpDIBBits,				// lpBits
		lpbi,					// lpBitsInfo
		DIB_RGB_COLORS);		// wUsage
}

/*************************************************************************
 *
 * �̸� : Draw(HDC hDC, int nFrame, int dx, int dy)
 * ���� : hDC    - ��� ��ġ�� DC �ڵ�
 *        nFrame - ����� ������ ��ȣ
 *        dx     - ��� ��ġ ��ġ�� x ��ǥ
 *        dy     - ��� ��ġ ��ġ�� y ��ǥ
 * ��ȯ : ����.
 * ���� : ��� ��ġ ��ǥ (x,y) ��ġ�� nFrame ��° �������� ����Ѵ�.
 *
 ************************************************************************/

void IppAvi::DrawFrame(HDC hDC, int nFrame, int dx, int dy)
{
	DrawFrame(hDC, nFrame, dx, dy, GetWidth(), GetHeight());
}

/*************************************************************************
 *
 * �̸� : Draw(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop)
 * ���� : hDC    - ��� ��ġ�� DC �ڵ�
 *        nFrame - ����� ������ ��ȣ
 *        dx     - ����� ��ġ�� x ��ǥ
 *        dy     - ����� ��ġ�� y ��ǥ
 *        dw     - ����� ������ ���� ũ��
 *        dh     - ����� ������ ���� ũ��
 *        dwRop  - ������ ���۷��̼� ����.
 * ��ȯ : ����.
 * ���� : ��� ��ġ ��ǥ (dx,dy) ��ġ�� (dw, dh) ũ��� nFrame ��° ��������
 *        ����Ѵ�.
 *
 ************************************************************************/

void IppAvi::DrawFrame(HDC hDC, int nFrame, int dx, int dy, int dw, int dh, DWORD dwRop)
{
	BYTE* pDib = (BYTE*)AVIStreamGetFrame(m_pVideoFrame, nFrame);
	if (!pDib)
		return;

	LPBITMAPINFO lpbi;
	LPSTR lpDIBBits;

	lpbi = (LPBITMAPINFO)pDib;

	if (lpbi->bmiHeader.biBitCount == 8)
		lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER) + 1024;
	else
		lpDIBBits = (LPSTR)pDib + sizeof(BITMAPINFOHEADER);

	::SetStretchBltMode(hDC, COLORONCOLOR);
	::StretchDIBits(hDC,	// hDC
		dx,					// XDest
		dy,					// YDest
		dw,					// nDestWidth
		dh,					// nDestHeight
		0,					// XSrc
		0,					// YSrc
		m_nWidth,			// nSrcWidth
		m_nHeight,			// nSrcHeight
		lpDIBBits,			// lpBits
		lpbi,				// lpBitsInfo
		DIB_RGB_COLORS,		// wUsage
		SRCCOPY);			// dwROP
}

/*************************************************************************
 *
 * �̸� : GetFrame(int nFrame, IppDib& dib)
 * ���� : nFrame - ���� ������ ��ȣ
 *        dib    - ���� �������� ������ IppDib ��ü
 * ��ȯ : �����ϸ� TRUE, �����ϸ� FALSE�� ��ȯ.
 * ���� : nFrame ��° �������� dib �� �����Ѵ�.
 *
 ************************************************************************/

BOOL IppAvi::GetFrame(int nFrame, IppDib& dib)
{
	LPVOID lpDib;
	LPSTR lpDIBBits;
	LPBITMAPINFO lpbi;

	lpDib = AVIStreamGetFrame(m_pVideoFrame, nFrame);
	lpbi = (LPBITMAPINFO)lpDib;

	if (lpbi->bmiHeader.biBitCount == 8)
		lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER) + 1024;
	else
		lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER);

	if (lpbi->bmiHeader.biBitCount == 8)
	{
		lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER) + 1024;

		dib.CreateGrayBitmap(m_nWidth, m_nHeight);
		memcpy(dib.GetBitmapInfoAddr(), lpDib, lpbi->bmiHeader.biSize + 1024 + lpbi->bmiHeader.biSizeImage);
	}
	else if (lpbi->bmiHeader.biBitCount == 24)
	{
		lpDIBBits = (LPSTR)lpDib + sizeof(BITMAPINFOHEADER);

		dib.CreateRgbBitmap(m_nWidth, m_nHeight);
		memcpy(dib.GetBitmapInfoAddr(), lpDib, lpbi->bmiHeader.biSize + lpbi->bmiHeader.biSizeImage);
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}