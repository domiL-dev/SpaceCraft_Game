#include "Planet.h"

//Initialize the position of the Planet
Planet::Planet() : mPosX{SCREEN_WIDTH/2-150}, mPosY{SCREEN_HEIGHT/2-150} {

}

int Planet::getmPosX() {
	return mPosX;
}

int Planet::getmPosY() {
	return mPosY;
}

void Planet::render(LTexture& gPlanetTexture)
{
	//Show the SpaceCraft
	gPlanetTexture.render(mPosX, mPosY);
}
