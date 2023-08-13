#pragma once
#include <Object.h>
#include <string>
#include <Vec2d.h>

class Stats : public Object
{
private:
	Vec2d mPOS{ 20,16 };
	int mLevel{}, mLines{}, mScore{};

public:
	void draw(ScreenBuffer& screen) override;
	void addScore(int completedLines);
	void restart();
	int getLevel();
};