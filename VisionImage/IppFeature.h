#pragma once

#include "IppImage.h"

void IppEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge); // 肺滚明
void IppEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge); // 橇府拉
void IppEdgeSobel(IppByteImage& img, IppByteImage& imgEdge); // 家骇
void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high); // 某聪
