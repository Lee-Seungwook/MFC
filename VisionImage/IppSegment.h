#pragma once

#include <vector>
#include "IppImage.h"

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold); // ����ȭ ����
int  IppBinarizationIterative(IppByteImage& imgSrc); // ����ȭ �Ӱ谪 ����