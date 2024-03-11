#include "SpaceCraft.h"
#include <iostream>

const double SpaceCraft::DOT_VEL = 2.0;
const double SpaceCraft::ANG_VEL = 3.0;


SpaceCraft::SpaceCraft() :mPosX{ SCREEN_WIDTH / 2 }, mPosY{ SCREEN_HEIGHT / 2 }, vX{ 0 }, vY{ 0 }, mAlpha{ 0 }, mAngVel{ 0 },
            VEL_VEC { 0.0, DOT_VEL }, DOT_VEL_X{ 0.00 }, DOT_VEL_Y{ 0.00 }
{
	
	//Ínitialize the angle of the Rotation Matrix
	rotation.angle() = mAlpha;

}

void SpaceCraft::rotation_Matrix() {
	rotation.angle() = mAlpha * M_PI / 180.0; //Set the angle of the Rotation Matrix dependend on the orientation of the Spacecraft

	std::cout << mAlpha << ":mAlpha" << std::endl;
	std::cout << VEL_VEC << ":VEL_VEC" << std::endl;
	//double rotationangle = rotation.angle() * 180 / M_PI % 360;
	std::cout << rotation.angle() << "° :Rotationsangle" << std::endl;

	VEL_VEC_rotated = rotation * VEL_VEC; //Multiplie the Velocity Vector with the Rotation Matrix

	DOT_VEL_X = VEL_VEC_rotated.x();				//X-Coordinates of the rotated Velocity Vector
	std::cout << DOT_VEL_X << ":x" << std::endl;
	DOT_VEL_Y = VEL_VEC_rotated.y();				//Y-Coordinates of the rotated Velocity Vector
	std::cout << DOT_VEL_Y << ":y" << std::endl;

	std::cout << vX << ":vX" << std::endl;
	std::cout << vY << ":vY" << std::endl;
	std::cout << mAngVel << ":mAngVel" << std::endl;
}

void SpaceCraft::handleEvent(SDL_Event& e)
{
	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: vY -= DOT_VEL_Y; vX -= DOT_VEL_X; break;
		case SDLK_DOWN: vY += DOT_VEL_Y; vX += DOT_VEL_X; break;
		
		case SDLK_LEFT: mAngVel -= ANG_VEL;break;
		case SDLK_RIGHT: mAngVel += ANG_VEL;break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		
		//case SDLK_UP: vY += DOT_VEL_Y; vX += DOT_VEL_X; break;
		//case SDLK_DOWN: vY -= DOT_VEL_Y; vX -= DOT_VEL_X; break;
		

		case SDLK_LEFT: mAngVel += ANG_VEL;break;
		case SDLK_RIGHT: mAngVel -= ANG_VEL;break;
		
		}
	}

	
}

void SpaceCraft::move(Planet& planet, LTexture& gSpaceCraftTexture, LTexture& gPlanetTexture)
{
	
	//If the SpaceCraft went too far to the left or right
	if ((mPosX + gSpaceCraftTexture.getCenterX() < 0))
	{
		//Move back
		vX = 0;
		vY = 0;
		mPosX += 1; 
	}
	else if ((mPosX + gSpaceCraftTexture.getCenterX() > SCREEN_WIDTH))
	{
		vX = 0; vY = 0;
		mPosX -= 1;
	}

	//If the SpaceCraft went too far up or down
	if (mPosY + gSpaceCraftTexture.getCenterY() < 0)
	{
		//Move back
		vX = 0; vY = 0;
		mPosY += 1; 
	}
	else if (mPosY + gSpaceCraftTexture.getCenterY() > SCREEN_HEIGHT)
	{
		vX = 0; vY = 0;
		mPosY -= 1;
	}

	

	//Rotate the Spacecraft
	mAlpha += mAngVel;

	//Move the Spacecraft
	if (n++ % 2 == 0) {
		mPosX += vX;
		mPosY += vY;
	};
	n++;
	//____________________
	rotation.angle() = (mAlpha * M_PI) / 180.0; //Set the angle of the Rotation Matrix dependend on the orientation of the Spacecraft

	VEL_VEC_rotated = rotation * VEL_VEC; //Multiplie the Velocity Vector with the Rotation Matrix

	DOT_VEL_X = VEL_VEC_rotated.x();				//X-Coordinates of the rotated Velocity Vector
	DOT_VEL_Y = VEL_VEC_rotated.y();				//Y-Coordinates of the rotated Velocity Vector

}

void SpaceCraft::render(SDL_Renderer* renderer,LTexture& gSpaceCraftTexture)
{
	//Show the SpaceCraft
	gSpaceCraftTexture.render(mPosX, mPosY, NULL, mAlpha);
	//
	
}

std::array<int,2> SpaceCraft::getCenterCoords(LTexture& gSpaceCraftTexture) {
	int x = mPosX + gSpaceCraftTexture.getCenterX();
	int y = mPosY + gSpaceCraftTexture.getCenterY();

	std::array<int, 2> CenterCoords = { x,y };
	return CenterCoords;
}

std::array<int, 2> SpaceCraft::getLaserVelCoords() {
	int x = DOT_VEL_X*10 - vX;
	int y = DOT_VEL_Y*10 - vY;

	std::array<int, 2> VelCoords = { x,y };
	return VelCoords;
	
}

double SpaceCraft::getaX() {
	return vX;
}

double SpaceCraft::getaY() {
	return vY;
}

void SpaceCraft::manipulate_aX(double aX1) {
	aX_Planet = aX1 ;
}

void SpaceCraft::manipulate_aY(double aY1) {
	aY_Planet = aY1;
}

//declare getters for Coordinates to Visualize Acceleration Arrows
int SpaceCraft::getmPosX() {
	return mPosX;
}

int SpaceCraft::getmPosY() {
	return mPosY;
}

//declare getters for Vector Top Coordinates of Acceleration Vector through engine
int SpaceCraft::getXtopAcc() {
	return static_cast<int>(AccLengthFaktor * vX);
}
int SpaceCraft::getYtopAcc() {
	return static_cast<int>(AccLengthFaktor * vY);
}



