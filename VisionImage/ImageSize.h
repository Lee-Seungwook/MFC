#pragma once

#include "IppImage.h"

void IppResizeNearest(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
void IppResizeNearest(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh);

void IppResizeBilinear(IppByteImage& imgSrc, IppByteImage& imgDst, int nw, int nh);
void IppResizeBilinear(IppRgbImage& imgSrc, IppRgbImage& imgDst, int nw, int nh);
