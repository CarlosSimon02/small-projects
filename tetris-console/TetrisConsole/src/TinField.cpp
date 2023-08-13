#include <TinField.h>

TinField::TinField(Field& field, TinQueue& queue) : mField{ field }, mQueue{ queue }
{
	spawn();
}

//public

void TinField::draw(ScreenBuffer& screen)
{
	for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
	{
		if (mCurrShape[i] == 'O' && mPOS.y + mOrientation[i].y > 3)
			screen[mOrientation[i].sum(SWIDTH) + mPOS.sum(SWIDTH) + mField.getPOS().sum(SWIDTH)] = mCurrShape[i];
	}

	//fall down
	mSpeedCount++;
	if (mSpeedCount >= mSPEED)
	{
		move(true, { 0,1 });
		mSpeedCount = 0;
	}

	if (mStop)
	{
		mQueue.randFutShape();
		storeToField();
		spawn();
		if (mField.isGameOver()) mField.clearFieldBuffer();
		mStop = false;
	}
}

void TinField::move(bool key, Vec2d dir)
{
	Vec2d tempPOS = mPOS;
	if (key)
	{
		mPOS.x += dir.x;
		mPOS.y += dir.y;
		if (isGridOccupied())
		{
			mPOS = tempPOS;
			if (dir.y == 1) mStop = true;
		}	
	}

}

void TinField::rotate(bool key)
{
	mCenter = mOrientation[5];
	Vec2d tempOrientation[8]{}, tempPOS = mPOS;
	for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++) tempOrientation[i] = mOrientation[i];


	if (key && mCurrShape != mSHAPE[3])
	{
		for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
		{
			int temp = mOrientation[i].x;
			mOrientation[i].x = mCenter.x - (mOrientation[i].y - mCenter.y);
			mOrientation[i].y = mCenter.y + (temp - mCenter.x);
		}

		for (size_t j = 0; j <= 5; j++)
		{
			if (isGridOccupied() && j<3)
			{
				mPOS.x += (mCenter.x > overlap.x) ? 1 : -1;
			}
			else if (isGridOccupied() && j >= 3 && j < 5)
			{
				mPOS.x = tempPOS.x;
				mPOS.y += (mCenter.y > overlap.y) ? 1 : -1;
			}
			else if (isGridOccupied() && j == 5)
			{
				for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
					mOrientation[i] = tempOrientation[i];
				mPOS = tempPOS;
			}
		}
	}
}

void TinField::fastDown(bool key)
{
	if (key) mSPEED = 5;
}

void TinField::forceDown(bool key)
{
	if (key)
	{
		while (!isGridOccupied()) mPOS.y++;
		mPOS.y--;
		mSpeedCount = mSPEED;
	}
}

void TinField::setSpeed(int level)
{
	mSPEED = 50 - level * 5;
}

//private
void TinField::spawn()
{
	mPOS = { mSPAWNPOINT };
	mCurrShape = mQueue.getCurrShape();
	for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
	{
		mOrientation[i].x = i % 2;
		mOrientation[i].y = (int)(floor(i / 2));
	}
}

bool TinField::isGridOccupied()
{
	for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
	{
		if (mField[mOrientation[i].sum(mField.getDIM().x) + mPOS.sum(mField.getDIM().x)] != ' ' && mCurrShape[i] == 'O')
		{
			overlap = mOrientation[i];
			return true;
		}
	}
	return false;
}

void TinField::storeToField()
{
	for (size_t i = 0; i < sizeof(mOrientation) / sizeof(Vec2d); i++)
	{
		if (mCurrShape[i] == 'O') mField[mOrientation[i].sum(mField.getDIM().x) + mPOS.sum(mField.getDIM().x)] = mCurrShape[i];
	}
}