#pragma once
#include "IppImage.h"

void IppFilterWeightedMean(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterGaussian(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma);

void IppFilterMedian(IppByteImage& imgSrc, IppByteImage& imgDst);