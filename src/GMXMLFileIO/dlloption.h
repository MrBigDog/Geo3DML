#pragma once

#define EXPORT_LIB // ǿ��Ϊ��̬��



#ifdef EXPORT_LIB
#define DLL_OPTION

#else
#ifdef EXPORT_DLL

#include <string>
#include <vector>

using namespace std;

#define DLL_OPTION __declspec(dllexport)  
#else  
#define DLL_OPTION __declspec(dllimport)  
#endif

#endif
