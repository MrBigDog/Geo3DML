#pragma once
#include "Export.h"

// �����ĳ���һ���ԭ�Ķ�ռ1/3�Ĵ洢�ռ䣬�뱣֤base64code���㹻�Ŀռ�
SAXREADER_EXPORT int Base64Encode(char * base64code, const char * src, int src_len = 0);
SAXREADER_EXPORT int Base64Decode(char * buf, const char * base64code, int src_len = 0);