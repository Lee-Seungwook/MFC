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

	//v.resize(size + 1); // reserve ��� �� �� Ÿ�� ������ ������, resize ��� �� vector�� ���� ���� �� ��...

	//copy(p, p + size, v.begin()); // ���� ��ҿ� �����ϴ� ���� (ù ��°�� ���� ����, �ι� °�� ���� ������, �� ��°�� ������ ���)
	//
	//if (!v.empty())
	//{
	//	for (int i = 0; i < size; i++)
	//	{
	//		// v[i] = 255 - v[i];
	//		v.push_back(255 - v[i]);
	//	}
	//	cout << "Vector ���" << endl;
	//	cout << "Vector[125] : " << v[99] << endl;
	//}
	//else if (v.empty())
	//{
	//	
	//	cout << "�迭 ���" << endl;
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

	// ������׷� ���
	int cnt[256];
	memset(cnt, 0, sizeof(int) * 256);
	for (int i = 0; i < size; i++)
		cnt[p[i]]++;

	// ������׷� ����ȭ(histogram normalization)
	for (int i = 0; i < 256; i++)
	{
		histo[i] = static_cast<float>(cnt[i]) / size;
	}
}
