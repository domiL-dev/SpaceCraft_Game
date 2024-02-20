#pragma once
#include "header.h"
#include "LTexture.h"
#include "SpaceCraft.h"
#include "Planet.h"
#include <iostream>


class ACCvector
{public:
	ACCvector();

	void render(SDL_Renderer* renderer, LTexture& gSpaceCraftTexture, LTexture& gPlanetTexture, SpaceCraft& SpaceCraft, Planet& Planet);


private:
	
};

