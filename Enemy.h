#pragma once
#include "header.h"
#include "LTexture.h"

class Enemy
{public:
	Enemy(int PosX, int PosY);

	void render(SDL_Renderer* renderer, LTexture& gEnemyTexture);

private:
	//Position Coords of Enemy Spacecraft
	int mPosX, mPosY, delta_mPosX, delta_mPosY;
	//Orientation of Enemy Spacecraft
	double mAlpha;
};

