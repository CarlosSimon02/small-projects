#pragma once

#include "olcConsoleGameEngineOOP.h"

struct Camera
{
	const float FOV{ 3.14159f / 4.f };

	float dir{0.f};
	olc::vec2df pos{ 8.f,8.f };
};