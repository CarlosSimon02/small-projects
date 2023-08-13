#pragma once

struct Vec2d
{
	int x, y;

	int sum(int width)
	{
		return x + (y * width);
	}
};