#include "pch.h"
#include "ImageSize.h"

#include "IppImage.h"
#include "IppConvert.h"

void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	double rx, ry;
	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);
			x = static_cast<int>(rx + 0.5);
			y = static_cast<int>(ry + 0.5);

			if (x >= w) x = w - 1;
			if (y >= h) y = h - 1;

			pDst[j][i] = pSrc[y][x];
		}
}

void IppResizeNearest(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, x, y;
	double rx, ry;
	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1); // 확대 비율로 나누어줌
			ry = static_cast<double>(h - 1) * j / (nh - 1);
			x = static_cast<int>(rx + 0.5); // 정수 값 변환 (반올림 하여), 참조할 원본 영상 좌표 
			y = static_cast<int>(ry + 0.5);

			if (x >= w) x = w - 1;
			if (y >= h) y = h - 1;

			pDst[j][i].r = pSrc[y][x].r;
			pDst[j][i].g = pSrc[y][x].g;
			pDst[j][i].b = pSrc[y][x].b;
		}
}


void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, x1, y1, x2, y2;
	double rx, ry, p, q, value;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1);
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			x1 = static_cast<int>(rx);
			y1 = static_cast<int>(ry);

			x2 = x1 + 1; if (x2 == w) x2 = w - 1;
			y2 = y1 + 1; if (y2 == h) y2 = h - 1;

			p = rx - x1;
			q = ry - y1;

			value = (1. - p) * (1. - q) * pSrc[y1][x1]
				+ p * (1. - q) * pSrc[y1][x2]
				+ (1. - p) * q * pSrc[y2][x1]
				+ p * q * pSrc[y2][x2];

			pDst[j][i] = static_cast<BYTE>(limit(value + .5));
		}
}


void IppResizeBilinear(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(nw, nh);

	RGBBYTE** pSrc = imgSrc.GetPixels2D();
	RGBBYTE** pDst = imgDst.GetPixels2D();

	int i, j, x1, y1, x2, y2;
	double rx, ry, p, q, Rvalue, Gvalue, Bvalue;

	for (j = 0; j < nh; j++)
		for (i = 0; i < nw; i++)
		{
			rx = static_cast<double>(w - 1) * i / (nw - 1); // 확대 비율로 나누어줌
			ry = static_cast<double>(h - 1) * j / (nh - 1);

			x1 = static_cast<int>(rx); // rx, ry 좌표를
			y1 = static_cast<int>(ry);

			x2 = x1 + 1; if (x2 == w) x2 = w - 1; // 같은 경우에는 맨 가장자리의 픽셀 값을 참조하도록 한다.
			y2 = y1 + 1; if (y2 == h) y2 = h - 1; // 둘러싼 4개의 픽셀 좌표를 나타냄

			p = rx - x1;
			q = ry - y1;

			Rvalue = (1. - p) * (1. - q) * pSrc[y1][x1].r + p * (1. - q) * pSrc[y1][x2].r
				+ (1. - p) * q * pSrc[y2][x1].r + p * q * pSrc[y2][x2].r; // 양선형 보간법을 적용하여 픽셀 값을 설정

			Gvalue = (1. - p) * (1. - q) * pSrc[y1][x1].g + p * (1. - q) * pSrc[y1][x2].g
				+ (1. - p) * q * pSrc[y2][x1].g + p * q * pSrc[y2][x2].g; // 양선형 보간법을 적용하여 픽셀 값을 설정

			Bvalue = (1. - p) * (1. - q) * pSrc[y1][x1].b + p * (1. - q) * pSrc[y1][x2].b
				+ (1. - p) * q * pSrc[y2][x1].b + p * q * pSrc[y2][x2].b; // 양선형 보간법을 적용하여 픽셀 값을 설정

			pDst[j][i].r = static_cast<BYTE>(limit(Rvalue + .5)); // 반올림하여 픽셀 값으로 저장
			pDst[j][i].g = static_cast<BYTE>(limit(Gvalue + .5)); // 반올림하여 픽셀 값으로 저장
			pDst[j][i].b = static_cast<BYTE>(limit(Bvalue + .5)); // 반올림하여 픽셀 값으로 저장
		}
}
