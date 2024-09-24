#include "Planet.h"

//Initialize the position of the Planet
Planet::Planet() : mPosX{ SCREEN_WIDTH / 2 - 150 }, mPosY{ SCREEN_HEIGHT / 2 - 150 }, health{ 100 } {

}

int Planet::getmPosX() {
	return mPosX;
}

int Planet::getmPosY() {
	return mPosY;
}

Uint8 Planet::get_health() {
	return health;
}

void Planet::damage(collision_type type) {
	switch (type) {

	case with_lasershot: health >= 5 ?  health -= 5 : health = 0 ;
		break;

	case with_spacecraft: health >= 10 ? health -= 10 : health = 0;
		break;

	case with_enemy: health >= 15 ? health -= 15: health = 0;
		break;

	case no_collision:
		break;
	}
}

void Planet::render(LTexture& gPlanetTexture)
{
	//Show the SpaceCraft
	gPlanetTexture.render(mPosX, mPosY);

}
