#pragma once

#include <Object.h>
#include <Vec2d.h>
#include <vector>
#include <chrono>
#include <Stats.h>

class Field : public Object
{
private:
	static constexpr Vec2d mDIM{ 12,25 };
	Vec2d mPOS{ 3,0 };
	Stats& mStats;
	wchar_t mFieldBuff[mDIM.x * mDIM.y];
	std::vector<int> mCompletedLine;

public:
	Field(Stats& stats);
	void draw(ScreenBuffer& screen) override;
	Vec2d getPOS();
	Vec2d getDIM();
	wchar_t& operator[](int index);
	std::vector<int> getCompletedLine();
	void clearCompletedLines();
	bool isGameOver();
	void clearFieldBuffer();
};
