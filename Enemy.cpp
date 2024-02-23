#include "Enemy.h"
#include <iostream>
#include <random>


Enemy::Enemy(int x, int y) :mPosX{ x }, mPosY{ y } {
	//Generate random starting-Coords at boundaries and intitialize mPosX and mPoxY (starting Coords)
	std::random_device rand; 
	std::uniform_int_distribution<int> side_dist(1, 4),						//1= top, 2=bottom, 3=left, 4=right?
									   top2bottom_range(1, SCREEN_HEIGHT),  //Coords -> Range for left or right side
									   left2right_range(1, SCREEN_WIDTH) ;  //Coords -> Range for bottom or top side
							 
	switch (side_dist(rand)) {
	case 1:
		mPosY = 0;
		mPosX = left2right_range(rand);
		break;
	case 2:
		mPosY = SCREEN_HEIGHT;
		mPosX = left2right_range(rand);
		break;
	case 3:
		mPosY = top2bottom_range(rand);
		mPosX = 0;
		break;
	case 4:
		mPosY = top2bottom_range(rand);
		mPosX = SCREEN_WIDTH;
		break;
	}


	//Calculate delta from starting-Coords to Planet-Center-Coords (Middle of Screen)
	delta_mPosX = static_cast<int>(SCREEN_WIDTH / 2) - mPosX;
	delta_mPosY = static_cast<int>(SCREEN_HEIGHT / 2) - mPosY;

	//Calculate Enemy Spacecraft starting Orientation
	mAlpha = 90+atan2(delta_mPosY,delta_mPosX)*180/M_PI;
	std::cout << delta_mPosY << "/" << delta_mPosX << std::endl;
	std::cout << mAlpha << std::endl;
}

void Enemy::render(SDL_Renderer* renderer, LTexture& gEnemyTexture) {
	//Logic to maneuvre the Enemy Space-Craft to Planet-Center-Coords
	if (delta_mPosX < 0 && delta_mPosX != 0) {
	mPosX--; delta_mPosX++;
    }
	else if (delta_mPosX > 0 && delta_mPosX != 0) {
		mPosX++; delta_mPosX--;
	}
	if (delta_mPosY < 0 && delta_mPosY != 0) {
		mPosY--; delta_mPosY++;
	}
	else if (delta_mPosY > 0 && delta_mPosY != 0) {
		mPosY++; delta_mPosY--;
	}
	//update Orientation towards Planet-Center-Coords in deg, depending on actual Enemy-Coords/delta to Center
	mAlpha = 90 + atan2(delta_mPosY, delta_mPosX) * 180 / M_PI;

	if (delta_mPosX == 0 && delta_mPosY == 0) {
		mPosX = SCREEN_WIDTH;
		mPosY = 300;
		delta_mPosX = static_cast<int>(SCREEN_WIDTH / 2) - mPosX;
		delta_mPosY = static_cast<int>(SCREEN_HEIGHT / 2) - mPosY;
	}

	gEnemyTexture.render(mPosX, mPosY, NULL, mAlpha);
}



