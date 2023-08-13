#include <Field.h>

Field::Field(Stats& stats) : mStats(stats)
{
	clearFieldBuffer();
}

void Field::draw(ScreenBuffer& screen)
{
	for (Vec2d i{}; i.y < mDIM.y; i.y++)
	{
		for (i.x = 0; i.x < mDIM.x; i.x++)
		{
			screen[i.sum(SWIDTH) + mPOS.sum(SWIDTH)] = mFieldBuff[i.sum(mDIM.x)];
		}
	}
}

Vec2d Field::getPOS()
{
	return mPOS;
}

Vec2d Field::getDIM()
{
	return mDIM;
}

wchar_t& Field::operator[](int index)
{
	return mFieldBuff[index];
}

std::vector<int> Field::getCompletedLine()
{
	for (Vec2d i{}; i.y < mDIM.y; i.y++)
	{
		int counter{};
		for (i.x=1; i.x < mDIM.x-1; i.x++)
		{
			if (mFieldBuff[i.sum(mDIM.x)] == 'O') counter++;
			if (counter == mDIM.x - 2)
			{
				mCompletedLine.push_back(i.y);
				for (i.x=1; i.x < mDIM.x - 1; i.x++) mFieldBuff[i.sum(mDIM.x)] = '=';
			}
		}
	}
	mStats.addScore(mCompletedLine.size());
	return mCompletedLine;
}

void Field::clearCompletedLines()
{
	for (size_t i = 0; i < mCompletedLine.size(); i++)
	{
		for (size_t j = mCompletedLine[i]*mDIM.x; j >0; j--)
		{
			if (mFieldBuff[j] != '#' && mFieldBuff[j] != NULL && 
				mFieldBuff[j+mDIM.x] != '#' && mFieldBuff[j + mDIM.x] != NULL)
			{
				mFieldBuff[j + mDIM.x] = mFieldBuff[j];
				mFieldBuff[j] = ' ';
			}
		}
	}
	mCompletedLine.clear();
}

bool Field::isGameOver()
{
	for (size_t i = 0; i < 4 * mDIM.x; i++)
	{
		if (mFieldBuff[i] == 'O') return true;
	}
	return false;
}

void Field::clearFieldBuffer()
{
	for (Vec2d i{}; i.y < mDIM.y; i.y++)
	{
		for (i.x = 0; i.x < mDIM.x; i.x++)
		{
			mFieldBuff[i.sum(mDIM.x)] = (i.sum(mDIM.x) % mDIM.x == 0 ||
				i.sum(mDIM.x) % mDIM.x == mDIM.x - 1 ||
				i.y == mDIM.y - 1) ? '#' : ' ';

			if (i.sum(mDIM.x) < 4 * mDIM.x)
				mFieldBuff[i.sum(mDIM.x)] = (i.sum(mDIM.x) % mDIM.x == 0 ||
					i.sum(mDIM.x) % mDIM.x == mDIM.x - 1) ? NULL : ' ';
		}
	}
}