// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"

// 미리 컴파일된 헤더를 사용하는 경우 컴파일이 성공하려면 이 소스 파일이 필요합니다.

CString g_arString[10];
CSemaphore g_SP(3, 3); // 호출할 수 있는 스레드나 프로세스의 수를 설정