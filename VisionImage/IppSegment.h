#pragma once

#include <vector>
#include "IppImage.h"

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold); // 이진화 수행
int  IppBinarizationIterative(IppByteImage& imgSrc); // 이진화 임계값 결정