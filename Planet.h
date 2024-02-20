#pragma once
#include "header.h"
#include "LTexture.h"
class Planet
{
public:
	//The dimensions of the planet
	static const int PLANET_WIDTH = 300;
	static const int PLANET_HEIGHT = 300;

	//create object gPlanetTexture from Class LTexture
	//LTexture gPlanetTexture;

	//Initializes the variables
	Planet();

	// getter Methods for PlanetCenterPosition
	int getmPosX();
	int getmPosY();

	//Shows the Planet on the screen
	void render(LTexture& gPlanetTexture);

private:
	int mPosX, mPosY;
};

