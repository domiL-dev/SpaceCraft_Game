#pragma once
#include <cmath>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Geometry> 
#include "header.h"
#include "LTexture.h"
#include "Planet.h"


class ACCvector;

class SpaceCraft
{
public:
	//The dimensions of the SpaceCraft
	//static const int DOT_WIDTH;
	//static const int DOT_HEIGHT;

	//Maximum axis velocity of the SpaceCraft
	static const double DOT_VEL;

	//Maximum angular velocity ( in rad) of the Space Craft
	static const double ANG_VEL;

	//Velocity vector
	const Eigen::Vector2d VEL_VEC;

	Eigen::Vector2d VEL_VEC_rotated;

	// Create an AngleAxis object for rotation
	
	Eigen::Rotation2D<double> rotation;


	
	
	//Initializes the variables
	SpaceCraft();

	//Takes key presses and adjusts the SpaceCraft's velocity
	void handleEvent(SDL_Event& e);

	//Multiplies the Velocity Vector with the rotation Matrix
	void rotation_Matrix();

	//Moves the SpaceCraft
	void move(Planet& planet, LTexture& gSpaceCraftTexture, LTexture& gPlanetTexture);

	//Shows the SpaceCraft on the screen
	void render(SDL_Renderer* renderer, LTexture& gSpaceCraftTexture);

	//getters for Coordinates to Visualize Acceleration Arrows
	int getmPosX();
	int getmPosY();
	int getXtopAcc();
	int getYtopAcc();

	std::array<int, 2> getCenterCoords(LTexture& gSpaceCraftTexture);
	std::array<int, 2> getLaserVelCoords();

	double getaX();
	double getaY();

	void manipulate_aX(double aX1);
	void manipulate_aY(double aY1);

	//void renderAccDirection(SDL_Renderer* renderer);


private:
	friend class ACCvector;
	
	//The X and Y offsets of the SpaceCraft
	int mPosX, mPosY, n;

	//The velocity of the SpaceCraft
	double vX, vY;

	//total velocity of the SpaceCraft
	double aX_Planet{ 0.0 }, aY_Planet{ 0.0 };

	//The Orientation of the Spacecraft
	double mAlpha;

	//The angular velocity of the Spacecraft
	double mAngVel;

	//The X and Y component of the velocity Vector
	double DOT_VEL_X, DOT_VEL_Y;
};

