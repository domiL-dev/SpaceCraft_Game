#pragma once
#include "header.h"
#include "LTexture.h"

class Enemy
{public:
	Enemy();

	void render(SDL_Renderer* renderer, LTexture& gEnemyTexture, std::vector<LTexture>& gExplosionTexture);
	//returns X-Coordinates of Enemy
	int get_mPosX();
	//returns Y-Coordinates of Enemy
	int get_mPosY();
    //return Orientation of Enemy
	double get_mAlpha();
	//returns boolian whether collision detected or not
	bool get_collision_detected();
	//sets colliion_detected true
	void set_collision_detected(), set_collision_with_lasershot(), set_collision_with_spacecraft(), set_collision_with_planet();
	//returns collision type to handle UI and gameplay
	enum collision_type get_collision_type();
	//returns status if the spaceCraft is finally exploded
	bool get_exploded();

private:
	//Position Coords of Enemy Spacecraft
	int mPosX, mPosY, delta_mPosX, delta_mPosY;
	//Orientation of Enemy Spacecraft
	double mAlpha;
	//Flag: Collision detected
	bool collision_detected, collision_with_lasershot, collision_with_spacecraft, collision_with_planet;
	//Flag: visual effect finished ready to destroy object
	bool exploded;
	//counter to visualize explosion
	int cnt_explosion, i;

	//Frame Intervall for Explosion growing
	const int explosion_frame_intervall{ 10 };
};

