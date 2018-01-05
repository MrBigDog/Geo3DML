#pragma once

#include <windows.h>

class MyTimer
{
private:
	int _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;

public:
	float costTime;            //��ʱ,*1000000 = ΢��, 1��=1000000

	MyTimer(void)
	{
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		_freq = tmp.QuadPart;
		costTime = 0;
	}

	~MyTimer(void)
	{

	}

	void Start()            // ��ʼ��ʱ
	{
		QueryPerformanceCounter(&_begin);
	}

	float End()                // ������ʱ
	{
		QueryPerformanceCounter(&_end);
		costTime = ((_end.QuadPart - _begin.QuadPart)*1.0f / _freq);

		return costTime;
	}

	void Reset()            // ��ʱ��0
	{
		costTime = 0;
	}
};