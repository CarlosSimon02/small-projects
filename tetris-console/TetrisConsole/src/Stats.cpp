#include <Stats.h>

void Stats::draw(ScreenBuffer& screen)
{
	std::wstring text[3] = { L"LEVEL:   " + std::to_wstring(mLevel),
						 L"LINE/S:  " + std::to_wstring(mLines),
						 L"SCORE:   " + std::to_wstring(mScore) };
	for (Vec2d i{}; i.y < 6; i.y += 2)
	{
		for (i.x = 0; i.x < text[i.y / 2].size(); i.x++)
		{
			screen[i.sum(SWIDTH) + mPOS.sum(SWIDTH)] = text[i.y / 2][i.x];
		}
	}
}

void Stats::addScore(int completedLines)
{
	mLines += completedLines;
	mScore += completedLines * completedLines * 100;
	mLevel = mLines / 10;
}

void Stats::restart()
{
	mLines = 0;
	mScore = 0;
	mLevel = 0;
}

int Stats::getLevel()
{
	return mLevel;
}