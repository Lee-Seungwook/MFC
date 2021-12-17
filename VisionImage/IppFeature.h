#pragma once

#include <vector>
#include "IppImage.h"

class IppPoint
{
public:
	int x;
	int y;

public:
	IppPoint() : x(0), y(0) {}
	IppPoint(int _x, int _y) : x(_x), y(_y) {}
};

class IppLineParam
{
public:
	double rho;
	double ang;
	int vote;

public:
	IppLineParam() : rho(0), ang(0), vote(0) {}
	IppLineParam(double r, double a, int v) : rho(r), ang(a), vote(v) {}
};

inline bool operator< (const IppLineParam& lhs, const IppLineParam& rhs)
{
	return lhs.vote > rhs.vote;
}


void IppEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge); // 로버츠
void IppEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge); // 프리윗
void IppEdgeSobel(IppByteImage& img, IppByteImage& imgEdge); // 소벨
void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high); // 캐니

void IppHoughLine(IppByteImage& img, std::vector<IppLineParam>& lines, int threshold = 60); // 허프 변환 
void IppDrawLine(IppByteImage& img, IppLineParam line, BYTE c); // 직선의 시작 좌표와 끝 좌표를 계산하여 밑의 함수를 호출
void IppDrawLine(IppByteImage& img, int x1, int y1, int x2, int y2, BYTE c); // 비트맴에 시작 좌표부터 끝 좌표까지 그레이스케일 값 C를 이요하여 직선을 그린다.

