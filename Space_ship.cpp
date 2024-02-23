

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Headers
#include "header.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Planet.h"
#include "SpaceCraft.h"
#include "Enemy.h"
#include "ACCvector.h"
#include "LaserShot.h"



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPlanetTexture;


//Charakter-Spacecraft textures
LTexture gSpaceCraftTexture;

//Enemy-Spacecraft texture
LTexture gEnemyTexture;

int n = 0; 
int m = 0;



//LTexture gBackgroundTexture;

//______________________________________________________________

//The SpaceCraft that will move around on the screen


//SpaceCraft methods implementation


//_______________________________________________________________


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SpaceCraft_Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Planet texture
	if (!gPlanetTexture.loadFromFile("SpaceCraft_Game/Planet.PNG"))
	{
		printf("Failed to load Planet texture!\n");
		success = false;
	}

	//Load SpaceCraft texture
	if (!gSpaceCraftTexture.loadFromFile("SpaceCraft_Game/space_craft5.png"))
	{
		printf("Failed to load SpaceCraft texture!\n");
		success = false;
	}

	//Load EnemySpaceCraft texture
	if (!gEnemyTexture.loadFromFile("SpaceCraft_Game/Enemy_Texture_1.png"))
	{
		printf("Failed to load Enemy SpaceCraft texture!\n");
		success = false;
	}



	//Load surface texture
	/*if (!gBackgroundTexture.loadFromFile("26_motion/Planet1.png"))
	{
		printf("Failed to load Planet texture!\n");
		success = false;
	}*/

	return success;
}

void close()
{
	//Free loaded images
	gSpaceCraftTexture.free();
	gPlanetTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//create Enemy

Enemy enemy(0, 100);

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Acceleration Vector Visualisation flag
			bool showAccVector = true;

			//Flag to create a Laser Object
			bool Laser_fired = false;

			//Vector for Laser Objects
			std::vector <std::unique_ptr<LaserShot>> LaserShots;

			//Event handler
			SDL_Event e;



			//The SpaceCraft that will be moving around on the screen
			SpaceCraft SpaceCraft;

			//The Planet wich will apppear
			Planet planet;

			//Accelration Vectors
			ACCvector acceleration;



			//While application is running
			while (!quit)
			{

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.key.keysym.sym == SDLK_v)
					{
						showAccVector = !showAccVector;
					}
					else if (e.key.keysym.sym == SDLK_SPACE)
					{
						if (m > 5) {
							Laser_fired = true;
							m = 0;
						}
				}
					m++;
				//Handle input for the SpaceCraft
				SpaceCraft.handleEvent(e);
				//SpaceCraft.rotation_Matrix();
			}


			if (Laser_fired) {
				//create LaserShot Object when Space was pressed - store in specified vector - reset Flage
				for (auto& element : LaserShots) {
 					if (element == nullptr) {
						element = std::move(std::make_unique<LaserShot>(SpaceCraft.getCenterCoords(gSpaceCraftTexture), SpaceCraft.getLaserVelCoords()));
						Laser_fired = false;
						std::cout << &element << std::endl;
					}
 				}
				if (Laser_fired) {
					LaserShots.push_back(std::move(std::make_unique<LaserShot>(SpaceCraft.getCenterCoords(gSpaceCraftTexture), SpaceCraft.getLaserVelCoords())));
					Laser_fired = false;
				}
				
				std::cout << "Size of LaserShots: " << LaserShots.size() << std::endl;
				
			}
			
			

			//Move the SpaceCraft
			SpaceCraft.move(planet, gSpaceCraftTexture, gPlanetTexture);

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);

			// render Laser Shots
			if (!LaserShots.empty()) {
				for (auto& element : LaserShots) {
					if (element != nullptr) {
						element->render(gRenderer);
						element->move();
					}
				}
			}

			planet.render(gPlanetTexture);

			//Render objects
			SpaceCraft.render(gRenderer, gSpaceCraftTexture);
			enemy.render(gRenderer, gEnemyTexture);
			if (showAccVector) {
				acceleration.render(gRenderer, gSpaceCraftTexture, gPlanetTexture, SpaceCraft, planet);
			} 
			
			//SpaceCraft.renderAccDirection(gRenderer);

			

			//destroy Laser Shots when out of bounds
			if (!LaserShots.empty()) {
				for (auto& element : LaserShots) {
					
					if (element != nullptr) {
						int x, y = 0;
						x = element->getX_bottom();
						y = element->getY_bottom();

						if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
 							element.reset();
					}
					
					
				}
			} 
			//avoid growing vector large in size
			/* if (LaserShots.size() == 3) {
				LaserShots.clear();
			}
			std::cout << "LaserShots - Size: " << LaserShots.size() << std::endl;
			*/

			//Update screen
			SDL_RenderPresent(gRenderer);




			//debug-test________________________
			//std::cout << "SpaceCraft CenterCoords: " << SpaceCraft.getCenterCoords(gSpaceCraftTexture).at(0) << std::endl;


		}
	}
}

	//Free resources and close SDL
	close();

	return 0;
}
