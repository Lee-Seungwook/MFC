#pragma once

#include <Windows.h>
#include <memory.h>
#include "RGBBYTE.h"
#include <vector>

using namespace std;

#define RGB2GRAY(r, g, b) (0.299*(r) + 0.587*(g) + 0.114*(b))

template<typename T>
class IppImage
{
protected:
	int     width;  // 영상의 가로 크기 (픽셀 단위)
	int     height; // 영상의 세로 크기 (픽셀 단위)
	T**     pixels; // 픽셀 데이터

public:
	// 생성자와 소멸자
	IppImage();
	IppImage(int w, int h);
	IppImage(const IppImage<T>& img);
	~IppImage();

	// 이미지 생성과 소멸
	void    CreateImage(int w, int h);
	void    DestroyImage();

	// 픽셀 값 접근
	T* GetPixels()   const {
		if (pixels) return pixels[0];
		else return NULL;
	}
	
	T** GetPixels2D() const { return pixels; }

	// 대입 연산자 재정의
	IppImage<T>& operator=(const IppImage<T>& img);
	template<typename U> IppImage<T>& operator=(const IppImage<U>& img);

	// 픽셀 값 설정
	template<typename U> void Convert(const IppImage<U>& img, bool use_limit = false);
	void    Convert(const IppImage<RGBBYTE> & img);

	// 영상 정보 반환
	int     GetWidth()    const { return width; }
	int     GetHeight()   const { return height; }
	int     GetSize()     const { return width * height; }
	bool    IsValid()     const { return (pixels != NULL); } // 실제 영상 데이터를 가지고 있는지 검사
};

// pixels 템플릿  클래스를 정의
typedef IppImage<BYTE> IppByteImage;
typedef IppImage<int> IppIntImage;
typedef IppImage<float> IppFloatImage;
typedef IppImage<double> IppDoubleImage;
typedef IppImage<RGBBYTE> IppRgbImage;
typedef IppImage<vector<BYTE>> IppVectorImage; // 임의 추가

template<typename T>
IppImage <T>::IppImage() : width(0), height(0), pixels(NULL)
{
}

template<typename T>
IppImage<T>::IppImage(int w, int h) : width(w), height(h), pixels(NULL) // 특정 크기의 영상을 생성하면서 초기화한다.
{
	pixels = new T*[sizeof(T*) * height];
	pixels[0] = new T[sizeof(T) * width * height];

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width;

	memset(pixels[0], 0, sizeof(T) * width * height); // 픽셀 값 초기화
}



template<class T>
IppImage<T>::IppImage(const IppImage<T>& img) : width(img.width), height(img.height), pixels(NULL) // 복사 생성자
{
	if (img.IsValid()) {
		pixels = new T*[sizeof(T*) * height];
		pixels[0] = new T[sizeof(T) * width * height];

		for (int i = 1; i < height; i++)
			pixels[i] = pixels[i - 1] + width;

		memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height); // 픽셀 값 복사
	}
}

template<typename T>
IppImage<T>::~IppImage()
{
	if (pixels != NULL) {
		delete[] pixels[0];
		delete[] pixels;
	}
}

template <typename T>
void IppImage<T>::CreateImage(int w, int h) // 명시적으로 영상을 생성하기 위해서이다.
{
	DestroyImage();

	width = w;
	height = h;

	pixels = new T*[sizeof(T*) * height];
	pixels[0] = new T[sizeof(T) * width * height];

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width;

	memset(pixels[0], 0, sizeof(T) * width * height); // 픽셀 값 초기화
}

template<typename T>
void IppImage<T>::DestroyImage() // 이미 생성되어 있는 영상 데이터를 없애기 위해서이다.
{
	if (pixels != NULL) {
		delete[] pixels[0];
		delete[] pixels;
		pixels = NULL;
	}
	width = height = 0;
}

template<typename T>
IppImage<T>& IppImage<T>::operator=(const IppImage<T>& img)
{
	if (this == &img)
		return *this;

	CreateImage(img.width, img.height);
	memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height);

	return *this;
}

template<typename T> template<typename U>
void IppImage<T>::Convert(const IppImage<U>& img, bool use_limit) // 형변환 하여 저장(IppImage 클래스끼리만 변환이 가능)
{
	CreateImage(img.GetWidth(), img.GetHeight());

	int size = GetSize();
	T* p1 = GetPixels();
	U* p2 = img.GetPixels();

	if (use_limit)
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(limit(p2[i]));

	else
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(p2[i]);
}

template<typename T>
void IppImage<T>::Convert(const IppImage<RGBBYTE>& img)
{
	CreateImage(img.GetWidth(), img.GetHeight());

	int size = GetSize();
	T* p1 = GetPixels();
	RGBBYTE* p2 = img.GetPixels();

	for (int i = 0; i < size; i++)
		p1[i] = static_cast<T>(RGB2GRAY(p2[i].r, p2[i].g, p2[i].b));
}

template<typename T>
inline T limit(const T& value)
{
	return ((value > 255) ? 255 : ((value < 0) ? 0 : value));
}

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}