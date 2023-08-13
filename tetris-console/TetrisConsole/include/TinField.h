#pragma once

#include <TinQueue.h>
#include <Field.h>
#include <cmath>

class TinField : public Tetromino
{
private:
	const Vec2d mSPAWNPOINT{ 5,0 };
	Field& mField;
	TinQueue& mQueue;
	Vec2d mCenter, overlap{};
	int mSPEED{ 50 }, mSpeedCount{};
	bool mStop{};

public:
	TinField(Field& field, TinQueue& queue);
	void draw(ScreenBuffer& screen) override;
	void move(bool key, Vec2d dir);
	void rotate(bool key);
	void fastDown(bool key);
	void forceDown(bool key);
	void setSpeed(int level);

private:
	void spawn();
	bool isGridOccupied();
	void storeToField();
};