#pragma once

#include "olcConsoleGameEngineOOP.h"
#include "Utils.h"

class Map
{
public:
	Map();
	std::wstring getFig();
	olc::vec2d<const int> getDim();
	const float getWallHeight() const;

private:
	std::wstring mFig{};
	olc::vec2d<const int> mDim{ 10,10 };
	const float wallHeight{ int(srn::HEIGHT) };
};