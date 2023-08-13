#include "Map.h"

Map::Map()
{
	mFig += L"OOOOOOOOOO";
	mFig += L"O.....O..O";
	mFig += L"OOOO..O..O";
	mFig += L"O.....O..O";
	mFig += L"OOOO.....O";
	mFig += L"O..O..O..O";
	mFig += L"O..O..O..O";
	mFig += L"O.....OOOO";
	mFig += L"O........O";
	mFig += L"OOOOOOOOOO";
}

std::wstring Map::getFig()
{
	return mFig;
}

olc::vec2d<const int> Map::getDim()
{
	return mDim;
}

const float Map::getWallHeight() const
{
	return wallHeight;
}