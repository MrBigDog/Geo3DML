#pragma once

#include "export.h"
//#ifndef _BASE64_INCLUDE__H__
//#define _BASE64_INCLUDE__H__

// �����ĳ���һ���ԭ�Ķ�ռ1/3�Ĵ洢�ռ䣬�뱣֤base64code���㹻�Ŀռ�
GMXMLFILEIO_EXPORT int Base64Encode(char * base64code, const char * src, int src_len = 0); 
GMXMLFILEIO_EXPORT int Base64Decode(char * buf, const char * base64code, int src_len = 0);
