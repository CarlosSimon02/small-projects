#pragma once

#include <string>
#include <Vec2d.h>
#include <Object.h>

class Tetromino : public Object
{
protected:
	const std::wstring mSHAPE[7] = {L"...OOOO.", //Z
									L"..O.OO.O", //S
									L"...OOO.O", //T
									L"..OOOO..", //O
									L".O.O.O.O", //I
									L"..O.O.OO", //L
									L"...O.OOO"};//J

	Vec2d mPOS, mOrientation[8];
	std::wstring mCurrShape;
};