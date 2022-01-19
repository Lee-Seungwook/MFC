#include "pch.h"
#include <math.h>
#include "IppEnhance.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void IppInverse(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = 255 - p[i];
	}
	//vector<BYTE> v;

	//v.resize(size + 1); // reserve 사용 시 런 타임 오류가 있으나, resize 사용 시 vector에 값이 들어가는 듯 함...

	//copy(p, p + size, v.begin()); // 뒤의 요소에 복사하는 것임 (첫 번째는 복사 시작, 두번 째는 복사 마지막, 세 번째는 대입할 대상)
	//
	//if (!v.empty())
	//{
	//	for (int i = 0; i < size; i++)
	//	{
	//		// v[i] = 255 - v[i];
	//		v.push_back(255 - v[i]);
	//	}
	//	cout << "Vector 사용" << endl;
	//	cout << "Vector[125] : " << v[99] << endl;
	//}
	//else if (v.empty())
	//{
	//	
	//	cout << "배열 사용" << endl;
	//}
	
}

void IppBrightness(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = limit(p[i] + n);
	}
}

void IppContrast(IppByteImage& img, int n)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i] = static_cast<BYTE>(limit(p[i] + (p[i] - 128) * n / 100));
	}
}

void IppGammaCorrection(IppByteImage& img, float gamma)
{
	float inv_gamma = 1.f / gamma;

	float gamma_table[256];
	for (int i = 0; i < 256; i++)
		gamma_table[i] = pow((i / 255.f), inv_gamma);

	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{


		p[i] = static_cast<BYTE>(limit(gamma_table[p[i]] * 255 + 0.5f));
	}
}

void IppHistogram(IppByteImage& img, float histo[256])
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	// 히스토그램 계산
	int cnt[256];
	memset(cnt, 0, sizeof(int) * 256);
	for (int i = 0; i < size; i++)
		cnt[p[i]]++;

	// 히스토그램 정규화(histogram normalization)
	for (int i = 0; i < 256; i++)
	{
		histo[i] = static_cast<float>(cnt[i]) / size;
	}
}
