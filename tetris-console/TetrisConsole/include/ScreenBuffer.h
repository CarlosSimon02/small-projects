#pragma once

#include <Windows.h>

const int SWIDTH{ 60 }, SHEIGHT{ 30 };

class ScreenBuffer
{
private:
	wchar_t mScreen[SWIDTH * SHEIGHT];
	HANDLE mHConsole{ CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL) };
	DWORD mBytesUsed{ 0 };

public:
	ScreenBuffer();
	void render();
	void clear();
	wchar_t& operator[](int index);
};