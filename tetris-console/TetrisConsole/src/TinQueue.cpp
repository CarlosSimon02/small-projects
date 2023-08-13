#include <TinQueue.h>

TinQueue::TinQueue()
{
	mPOS = { 20,4 };
	srand(time(NULL));
	mFutShape = mSHAPE[rand() % 7];
	mCurrShape = mFutShape;
	mFutShape = mSHAPE[rand() % 7];
}

void TinQueue::draw(ScreenBuffer& screen)
{
	std::wstring text{ L"NEXT:" };
	for (size_t i = 0; i < text.size(); i++)
	{
		screen[i + mPOS.sum(SWIDTH)] = text[i];
	}
	for (size_t i = 0; i < sizeof(mOrientation)/sizeof(Vec2d); i++)
	{
		if (mFutShape[i] == 'O') screen[(i % 2 * SWIDTH) - (i / 2) + mPOS.sum(SWIDTH) + (2 * SWIDTH + 5)] = mFutShape[i];
	}
}

std::wstring TinQueue::getCurrShape()
{
	return mCurrShape;
}

void TinQueue::randFutShape()
{
	srand(time(NULL));
	mCurrShape = mFutShape;
	mFutShape = mSHAPE[rand() % 7];
}