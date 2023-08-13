#include <ScreenBuffer.h>

ScreenBuffer::ScreenBuffer()
{
	clear();
	SetConsoleActiveScreenBuffer(mHConsole);
}

void ScreenBuffer::render()
{
	WriteConsoleOutputCharacter(mHConsole, mScreen, SWIDTH * SHEIGHT, { 0,0 }, &mBytesUsed);
}

void ScreenBuffer::clear()
{
	for (size_t i = 0; i < sizeof(mScreen)/sizeof(wchar_t); i++)
	{
		mScreen[i] = ' ';
	}
}

wchar_t& ScreenBuffer::operator[](int index)
{
	return mScreen[index];
}