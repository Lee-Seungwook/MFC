#include "pch.h"

#include "IppFilter.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <algorithm>

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

// 가중 평균값 필터
void IppFilterWeightedMean(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc; // 대입 연산자 오버로딩으로 클래스간 연산 가능, 이미지 복사

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int mask[3][3] = {
		{ 1, 2, 1 },
		{ 2, 4, 2 },
		{ 1, 2, 1 },
	};

	int i, j, m, n, sum;
	for (j = 1; j < h - 1; j++) // 최외곽 픽셀은 계산하지 않는다.
		for (i = 1; i < w - 1; i++) // 영상 픽셀
		{
			sum = 0;
			for (m = 0; m < 3; m++) // 마스크 배열
				for (n = 0; n < 3; n++)
				{
					sum += (pSrc[j - 1 + m][i - 1 + n] * mask[m][n]); // 영상 픽셀을 1부터 시작했기 때문에 1을 빼준다.
				}

			pDst[j][i] = static_cast<BYTE>(limit(sum / 16. + 0.5)); // 마스크의 총 합으로 나눠준다, 0.5는 반올림인듯
		}
}

// 가우시안 필터 구현
void IppFilterGaussian(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma)
{
	register int i, j, k, x;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	float** pDst = imgDst.GetPixels2D();

	//-------------------------------------------------------------------------
	// 1차원 가우시안 마스크 & 실수 연산을 위한 버퍼 이미지 생성
	//-------------------------------------------------------------------------

	int dim = static_cast<int>(2 * 4 * sigma + 1.0); // 마스크 크기 결정
	if (dim < 3) dim = 3; // 최소 마스크 크기를 3으로 지정
	if (dim % 2 == 0) dim++; // 짝수이면 홀수로 만들어줌
	int dim2 = dim / 2;

	IppFloatImage imgMask(dim, 1); // 가우시안 마스크로서 활용하기 위해 실수형 영상을 사용
	float* pMask = imgMask.GetPixels();

	for (i = 0; i < dim; i++)
	{
		x = i - dim2;
		pMask[i] = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * PI_F) * sigma);
	}

	IppFloatImage imgBuf(w, h);
	float** pBuf = imgBuf.GetPixels2D(); // 임시 저장을 위한 영상

	//-------------------------------------------------------------------------
	// 세로 방향 마스크 연산
	//-------------------------------------------------------------------------

	float sum1, sum2;
	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + j;

				if (x >= 0 && x < h)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pSrc[x][i]);
				}
			}

			pBuf[j][i] = sum2 / sum1;
		}

	//-------------------------------------------------------------------------
	// 가로 방향 마스크 연산
	//-------------------------------------------------------------------------

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + i;

				if (x >= 0 && x < w)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pBuf[j][x]);
				}
			}

			pDst[j][i] = sum2 / sum1; // 출력 영상에 저장
		}
}

// 미디언 필터
void IppFilterMedian(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	BYTE m[9];
	for (j = 1; j < h - 1; j++) // 중위 수를 계산하기 위한 반복문 밑 sort 함수 적용
		for (i = 1; i < w - 1; i++)
		{
			m[0] = pSrc[j - 1][i - 1]; m[1] = pSrc[j - 1][i]; m[2] = pSrc[j - 1][i + 1];
			m[3] = pSrc[j][i - 1]; m[4] = pSrc[j][i]; m[5] = pSrc[j][i + 1];
			m[6] = pSrc[j + 1][i - 1]; m[7] = pSrc[j + 1][i]; m[8] = pSrc[j + 1][i + 1];

			std::sort(m, m + 9); // 주소를 매개변수로 사용하기 때문에 배열의 주소를 넘겨준다.

			pDst[j][i] = m[4];
		}
}

// 라플라시안 필터
void IppFilterLaplacian(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, sum;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			sum = pSrc[j - 1][i] + pSrc[j][i - 1] + pSrc[j + 1][i] + pSrc[j][i + 1]
				- 4 * pSrc[j][i];

			pDst[j][i] = static_cast<BYTE>(limit(sum + 128));
		}
}

// 언샤프마스크 필터
void IppFilterUnsharpMask(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, sum;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			sum = 5 * pSrc[j][i]
				- pSrc[j - 1][i] - pSrc[j][i - 1] - pSrc[j + 1][i] - pSrc[j][i + 1];

			pDst[j][i] = static_cast<BYTE>(limit(sum));
		}
}

// 하이부스트 필터
void IppFilterHighboost(IppByteImage& imgSrc, IppByteImage& imgDst, float alpha)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j;
	float sum;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			sum = (4 + alpha) * pSrc[j][i]
				- pSrc[j - 1][i] - pSrc[j][i - 1] - pSrc[j + 1][i] - pSrc[j][i + 1];

			pDst[j][i] = static_cast<BYTE>(limit(sum + 0.5f));
		}
}
