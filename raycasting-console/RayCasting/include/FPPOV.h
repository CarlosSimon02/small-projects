#pragma once

#include "olcConsoleGameEngineOOP.h"
#include "Map.h"
#include "Camera.h"

class FPPOV :public olc::ConsoleGameEngineOOP
{
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	Camera cam;
	Map map;
};