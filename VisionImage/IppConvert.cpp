#include "pch.h"
#include <assert.h>
#include "IppConvert.h"

void IppDibToImage(IppDib& dib, IppByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 8);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D();

	// pixels[i]는 IppByteImage의 i번째 행의 픽셀 데이터 시작 주소
	// pDIBits는 DIB 구조에서 픽셀 데이터의 시작 위치를 나타냄
	// ws 변수는 DIB 구조에서 영상의 가로 한줄을 저장하기 위해 필요한 바이트 수를 나타냄, 4의 배수 형태
	// 픽셀 데이터는 상하가 뒤집힌 형태로 저장되기 때문에 i번째 행의 시작 위치는 [] 식으로 구한다.
	// ws 바이트 중 실제 의미 있는 픽셀 데이터는 w바이트이므로 해당 바이트만 복사한다.

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w);
	}
}

void IppDibToImage(IppDib& dib, IppRgbImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w * 3 + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	RGBBYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w * 3);
	}
}

void IppImageToDib(IppByteImage& img, IppDib& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE** pixels = img.GetPixels2D();

	dib.CreateGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w);
	}
}

void IppImageToDib(IppFloatImage& img, IppDib& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3;
	float** pixels = img.GetPixels2D();

	dib.CreateGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	int i, j;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pDIBits[(h - 1 - j) * ws + i] = static_cast<BYTE>(limit(pixels[j][i] + 0.5f)); // memcpy함수 사용이 불가하여 반복문으로 픽셀의 위치를 참조하였다.
		}
}

void IppImageToDib(IppRgbImage& img, IppDib& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w * 3 + 3) & ~3;
	RGBBYTE** pixels = img.GetPixels2D();

	dib.CreateRgbBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w * 3);
	}
}

// ptr 함수를 사용하여 영상의 각 행 시작 픽셀 주소를 얻는다.

void IppImageToMat(IppByteImage& img, cv::Mat& mat)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	mat.create(h, w, CV_8U);

	BYTE** pSrc = img.GetPixels2D();

	BYTE* pDst;
	for (int j = 0; j < h; j++)
	{
		pDst = mat.ptr<BYTE>(j);
		memcpy(pDst, pSrc[j], sizeof(BYTE) * w);
	}
}

void IppImageToMat(IppRgbImage& img, cv::Mat& mat)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	mat.create(h, w, CV_8UC3);

	RGBBYTE** pSrc = img.GetPixels2D();

	RGBBYTE* pDst;
	for (int j = 0; j < h; j++)
	{
		pDst = mat.ptr<RGBBYTE>(j);
		memcpy(pDst, pSrc[j], sizeof(RGBBYTE) * w);
	}
}

void IppMatToImage(cv::Mat& mat, IppByteImage& img)
{
	CV_Assert(mat.type() == CV_8UC1); // Grayscale img

	int w = mat.cols;
	int h = mat.rows;

	img.CreateImage(w, h);

	BYTE** pDSt = img.GetPixels2D();

	BYTE* pSrc;
	for (int j = 0; j < h; j++)
	{
		pSrc = mat.ptr<BYTE>(j);
		memcpy(pDSt[j], pSrc, sizeof(BYTE) * w);
	}
}

void IppMatToImage(cv::Mat& mat, IppRgbImage& img)
{
	CV_Assert(mat.type() == CV_8UC3); // True color Image

	int w = mat.cols;
	int h = mat.rows;

	img.CreateImage(w, h);

	RGBBYTE** pDst = img.GetPixels2D();

	RGBBYTE* pSrc;
	for (int j = 0; j < h; j++)
	{
		pSrc = mat.ptr<RGBBYTE>(j);
		memcpy(pDst[j], pSrc, sizeof(RGBBYTE) * w);
	}
}