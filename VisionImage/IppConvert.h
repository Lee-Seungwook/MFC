#pragma once

#include "IppImage.h"
#include "IppDib.h"
#include <opencv2/opencv.hpp>

void IppDibToImage(IppDib& dib, IppByteImage& img); // IppDib Ŭ������ IppImage Ŭ������ ��ȯ
void IppDibToImage(IppDib& dib, IppRgbImage& img); // IppDib ��ü�� ǰ�� �ִ� DIB ������ �׷��̽����� �����̸� IppByte image ���, Ʈ���÷��̸� IppRgbImage�� ���
void IppImageToDib(IppByteImage& img, IppDib& dib);  // IppImage Ŭ������ IppDib Ŭ������ ��ȯ
void IppImageToDib(IppFloatImage& img, IppDib& dib); // ������ ������ ������ �ʿ䰡 �ְų�, �Ǽ��� �������� �����Ǵ� ��찡 �ֱ� �����̴�.
void IppImageToDib(IppRgbImage& img, IppDib& dib);

// Mat Ŭ������ ��ȯ
void IppImageToMat(IppByteImage& img, cv::Mat& mat); // �׷��� ������
void IppImageToMat(IppRgbImage& img, cv::Mat& mat); // Ʈ�� �÷�

void IppMatToImage(cv::Mat& mat, IppByteImage& img);
void IppMatToImage(cv::Mat& mat, IppRgbImage& img);
