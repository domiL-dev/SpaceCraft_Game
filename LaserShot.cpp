#include "LaserShot.h"

LaserShot::LaserShot(std::array<int,2> CenterCoords, std::array<int,2> LaserVelCoords) : x_top{CenterCoords.at(0) - LaserVelCoords.at(0)*10}, y_top{CenterCoords.at(1) - LaserVelCoords.at(1)*10}, x_bottom{CenterCoords.at(0)}, y_bottom{CenterCoords.at(1)}, vX{LaserVelCoords.at(0)}, vY(LaserVelCoords.at(1))
{

}

void LaserShot::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 255);
	SDL_RenderDrawLine(renderer, x_bottom, y_bottom, x_top, y_top);
}

void LaserShot::move() {
	x_top -= vX; y_top -= vY; x_bottom -= vX; y_bottom -= vY;
}

int LaserShot::getX_bottom(){
	return x_bottom;
}

int LaserShot::getY_bottom(){
	return y_bottom;
}