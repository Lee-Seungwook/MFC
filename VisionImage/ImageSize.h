#pragma once

#include "IppImage.h"

void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);

void IppResizeCubic(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
double cubic_interpolation(double v1, double v2, double v3, double v4, double d);

void IppRotate(IppByteImage& imgSrc, IppByteImage& imgDst, double angle);

