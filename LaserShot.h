#pragma once
#include "header.h"

class LaserShot
{public:
	LaserShot(std::array<int,2> CenterCoords, std::array<int,2> LaserVelCoords);

	void render(SDL_Renderer* renderer);
	void move();
	int getX_bottom();
	int getY_bottom();

private:
	int x_top, y_top, x_bottom, y_bottom, vX, vY;
};

