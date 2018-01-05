   //#include "StdAfx.h"
#include "xmlBase64.h"
#include <string.h>

__inline char GetB64Char(int index)
{
	const char szBase64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	if (index >= 0 && index < 64)
		return szBase64Table[index];

	return '=';
}

// ��˫����ȡ���ֽ�
#define B0(a) (a & 0xFF)
#define B1(a) (a >> 8 & 0xFF)
#define B2(a) (a >> 16 & 0xFF)
#define B3(a) (a >> 24 & 0xFF)
// �����ĳ���һ���ԭ�Ķ�ռ1/3�Ĵ洢�ռ䣬�뱣֤base64code���㹻�Ŀռ�
int Base64Encode(char * base64code, const char * src, int src_len) 
{   
	if (src_len == 0)
		src_len = strlen(src);
	int len = 0;
	unsigned char* psrc = (unsigned char*)src;
	char * p64 = base64code;
	int i = 0;
	for ( i = 0; i < src_len - 3; i += 3)
	{
		unsigned long ulTmp = *(unsigned long*)psrc;
		register int b0 = GetB64Char((B0(ulTmp) >> 2) & 0x3F); 
		register int b1 = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
		register int b2 = GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F); 
		register int b3 = GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F); 
		*((unsigned long*)p64) = b0 | b1 << 8 | b2 << 16 | b3 << 24;
		len += 4;
		p64  += 4; 
		psrc += 3;
	}

	// ����������µĲ���3�ֽڵĶ�����
	if (i < src_len)
	{
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j)
		{
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		}

		p64[0] = GetB64Char((B0(ulTmp) >> 2) & 0x3F); 
		p64[1] = GetB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
		p64[2] = rest > 1 ? GetB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F) : '='; 
		p64[3] = rest > 2 ? GetB64Char((B2(ulTmp) << 2 >> 2) & 0x3F) : '='; 
		p64 += 4; 
		len += 4;
	}

	*p64 = '\0'; 

	return len;
}

__inline int GetB64Index(char ch)
{
	int index = -1;
	if (ch >= 'A' && ch <= 'Z')
	{
		index = ch - 'A';
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		index = ch - 'a' + 26;
	}
	else if (ch >= '0' && ch <= '9')
	{
		index = ch - '0' + 52;
	}
	else if (ch == '+')
	{
		index = 62;
	}
	else if (ch == '/')
	{
		index = 63;
	}

	return index;
}

// �����ĳ���һ���ԭ������ռ1/4�Ĵ洢�ռ䣬�뱣֤buf���㹻�Ŀռ�
int Base64Decode(char * buf, const char * base64code, int src_len) {
	if (src_len == 0)
		src_len = strlen(base64code);
	int len = 0;
	unsigned char* psrc = (unsigned char*)base64code;
	char * pbuf = buf;
	int i = 0;
	for ( i = 0; i < src_len - 4; i += 4) {
		unsigned long ulTmp = *(unsigned long*)psrc;
		int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
		int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
		*((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16;
		psrc  += 4; 
		pbuf += 3;
		len += 3;
	}
	// ����������µĲ���4�ֽڵĶ�����
	if (i < src_len) {
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j)
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		int b0 = (GetB64Index((char)B0(ulTmp)) << 2 | GetB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		*pbuf++ = b0;
		len  ++;
		if ('=' != B1(ulTmp) && '=' != B2(ulTmp)) {
			int b1 = (GetB64Index((char)B1(ulTmp)) << 4 | GetB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
			*pbuf++ = b1;
			len  ++;
		}
		if ('=' != B2(ulTmp) && '=' != B3(ulTmp)) {
			int b2 = (GetB64Index((char)B2(ulTmp)) << 6 | GetB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
			*pbuf++ = b2;
			len  ++;
		}
	} 
	*pbuf = '\0'; 
	return len;
} 

