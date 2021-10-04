#pragma once

#ifdef _DLL_MATH_ 
#define DLL_MATH _declspec(dllexport) 
#else 
#define DLL_MATH __declspec(dllimport) 
#endif 

DLL_MATH int SumXnY( int iX, int iY );


