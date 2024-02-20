#include "ACCvector.h"

ACCvector::ACCvector() {

}

void ACCvector::render(SDL_Renderer* renderer, LTexture& gSpaceCraftTexture, LTexture& gPlanetTexture, SpaceCraft& SpaceCraft, Planet& Planet) {

	//Coordinates for Acceleration Vector (engine)
	int x1 = SpaceCraft.getmPosX() + gSpaceCraftTexture.getCenterX();
	int y1 = SpaceCraft.getmPosY() + gSpaceCraftTexture.getCenterY();
	int x2 = x1 + SpaceCraft.getaX() * AccLengthFaktor;
	int y2 = y1 + SpaceCraft.getaY() * AccLengthFaktor;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

	//Mass of Spacecraft
	double mS = gSpaceCraftTexture.getWidth() * gSpaceCraftTexture.getHeight();

	//Mass of Planet
	double mP = gPlanetTexture.getHeight() * gPlanetTexture.getWidth();

	//Center of Planet
	double x_center_planet = Planet.getmPosX() + gPlanetTexture.getCenterX();
	double y_center_planet = Planet.getmPosY() + gPlanetTexture.getCenterY();

	//Distance Spacecraft -> Planet
	double x_distance_to_planet = x_center_planet-x1;
	double y_distance_to_planet = y_center_planet - y1;
	double distance_to_planet = sqrt(pow(x_distance_to_planet, 2) + pow(y_distance_to_planet,2));

	//std::cout << distance_to_planet << " :distance to planet" << std::endl;
	//Calculate Gravity Force
	//double F_g = G * (mS * mP) /pow(distance_to_planet, 2);
	double F_g = 1 / (distance_to_planet/200);
	
	//Calculate Acceleration of the Spacecraft through Gravity of Planet
	double aS = F_g / (mS);

	//Hier wird ein Faktor berechnet mit dem man die Anteile in x und y Richtung berechenen kann
	double Faktor = aS;//distance_to_planet;

	double aXPlanet = Faktor*x_distance_to_planet;

	double aYPlanet = Faktor*y_distance_to_planet;

	//std::cout << aXPlanet << ":aXPlanet" << std::endl;
	//std::cout << aYPlanet << ":aYPlanet" << std::endl;
	

	
	
	SpaceCraft.manipulate_aX(aXPlanet);
	SpaceCraft.manipulate_aY(aYPlanet);

	//int x3 = x_center_planet;
	//int y3 = y_center_planet;
	int x3 = x1 + aXPlanet*AccLengthFaktor;
	int y3 = y2 + aYPlanet*AccLengthFaktor;
	SDL_SetRenderDrawColor(renderer,0 ,255, 0, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x3, y3);

	
}