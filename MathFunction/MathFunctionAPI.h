#pragma once
#ifdef _DLL_MATH_
#define DLL_MATH _declspec(dllexport)
#else
#define DLL_MATH __declspec(dllimport)
#endif

DLL_MATH int SumXnY(int iX, int iY);
DLL_MATH int SubXnY(int iX, int iY);
DLL_MATH int DivXnY(int iX, int iY);
DLL_MATH int MulXnY(int iX, int iY);