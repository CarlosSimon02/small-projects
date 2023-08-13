#pragma once
#include <Windows.h>

class Keypress
{
private:
	int mKey;
	bool mFlag;

public:
	Keypress(int key) : mKey(key), mFlag(false)
	{

	}


	bool once()
	{
		if (GetAsyncKeyState(mKey) && !mFlag)
		{
			mFlag = true;
			return true;
		}
		else if (GetAsyncKeyState(mKey) == false)
		{
			mFlag = false;
		}
		return false;
	}

	bool repeated()
	{
		if (GetAsyncKeyState(mKey)) return true;
		else return false;
	}
};