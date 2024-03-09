#pragma once
#include "header.h"

class LaserShot
{public:
	LaserShot(std::array<int,2> CenterCoords, std::array<int,2> LaserVelCoords);

	void render(SDL_Renderer* renderer);
	void move();
	
	// returns x-Coords of bottom of laserhot
	int getX_bottom();
	// returns y-Coords of bottom of lasershot
	int getY_bottom();
	// returns x-Coords of top of lasershot
	int getX_top();
	// returns y-Coords of top of lasershot
	int getY_top();

private:
	int x_top, y_top, x_bottom, y_bottom, vX, vY;
};

