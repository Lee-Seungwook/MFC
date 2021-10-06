#pragma once

#ifdef _SHARE_MEMORY_ 
#define SHARE_MEMORY _declspec(dllexport) 
#else 
#define SHARE_MEMORY __declspec(dllimport) 
#endif



SHARE_MEMORY void SetValue(int iSet); 
SHARE_MEMORY int GetValue();


