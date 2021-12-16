#pragma once

#include <vector>
#include "IppImage.h"

//class IppLabelInfo
//{
//public:
//	std::vector<IppPoint> pixels;
//	int cx, cy;
//	int minx, miny, maxx, maxy;
//
//public:
//	IppLabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
//	{
//		pixels.clear();
//	}
//};

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold); // 이진화 수행
int  IppBinarizationIterative(IppByteImage& imgSrc); // 이진화 임계값 결정

// void IppContourTracing(IppByteImage& imgSrc, int sx, int sy, std::vector<IppPoint>& cp);