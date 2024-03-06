

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Headers
#include "header.h"
#include "Math_Functions.h"
#include "LTexture.h"
#include "LTimer.h"
#include "Planet.h"
#include "SpaceCraft.h"
#include "Enemy.h"
#include "ACCvector.h"
#include "LaserShot.h"
#include "Enemy.h"

#include <cstdlib>



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

//Explosion Texture Vector containing 4 objects 0->3 = small to big
std::vector<LTexture> gExplosionTexture(4);

int n = 0; 
int m = 0;
int cnt_Enemies = 0;
int Enemies_at_once = 1;
int Enemies_destroyed = 0;
int spawning_delay = 100;
bool Enemy_just_destroyed = false;
int spawning_delay_counter = spawning_delay;



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

	//Load Explosion texture
	for (int i = 0; i < 4; i++) {
		if (!gExplosionTexture[i].loadFromFile("SpaceCraft_Game/Explosion_" + std::to_string(i+1) + ".png"))
		{
			printf("Failed to load Explosion texture nr.!\n");
			std::cout << std::to_string(i + 1) << std::endl;
			success = false;
		}
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

	for (auto& element : gExplosionTexture) {
		element.free();
	}
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


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

/*-----------------------------------------------------------------------*/
			//Vector for Enemy Objects
			std::vector <std::unique_ptr<Enemy>> Enemies;
/*-----------------------------------------------------------------------*/

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

/*_____________________________________________________________________________________________________________*/
//create LaserShot Object when Space was pressed - store in specified vector - reset Flag
				if (Laser_fired) {
				for (auto& element : LaserShots) {
 					if (element == nullptr) {
						element = std::move(std::make_unique<LaserShot>(SpaceCraft.getCenterCoords(gSpaceCraftTexture), SpaceCraft.getLaserVelCoords()));
						Laser_fired = false;
						//std::cout << &element << std::endl;
					}
 				}
				if (Laser_fired) {
					LaserShots.push_back(std::move(std::make_unique<LaserShot>(SpaceCraft.getCenterCoords(gSpaceCraftTexture), SpaceCraft.getLaserVelCoords())));
					Laser_fired = false;
				}
				
				//std::cout << "Size of LaserShots: " << LaserShots.size() << std::endl;
				
			}
/*_____________________________________________________________________________________________________________*/
				if (Enemy_just_destroyed) {
					
					spawning_delay_counter--;
					if (spawning_delay_counter == 0) {
						Enemy_just_destroyed = false;
						spawning_delay_counter = spawning_delay;
					};
			}

            //create Enemy Object
			if (cnt_Enemies < Enemies_at_once && !Enemy_just_destroyed) {
				bool create_Enemy = true; // Flag for logic inside if Statement
			//create LaserShot Object when Space was pressed - store in specified vector - reset Flage
				for (auto& element : Enemies) {
					if (element == nullptr) {
						element = std::move(std::make_unique<Enemy>());
						cnt_Enemies++;
						create_Enemy = false;
						//std::cout << &element << std::endl;
					}
				}
				if (create_Enemy) {
					Enemies.push_back(std::move(std::make_unique<Enemy>()));
					cnt_Enemies++;
					create_Enemy = false;
				}
				std::cout << "Size of Enemies: " << Enemies.size() << std::endl;
				std::cout << "cnt_Enemies: " << cnt_Enemies << std::endl;
			}
/*_____________________________________________________________________________________________________________*/

			

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

			// render Enemies
			if (!Enemies.empty()) {
				for (auto& element : Enemies) {
					if (element != nullptr) {
						element->render(gRenderer, gEnemyTexture, gExplosionTexture);
/*_________________________________________________________________________________________*/
						//Purpose -> Collision detection, Visualize the skeleton => when laser hits the skelleton than sets collision_detected to true
						int x1 = Texture_Boundaries(Bottom_X,element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int y1 = Texture_Boundaries(Bottom_Y, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int x2 = Texture_Boundaries(Top_X, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int y2 = Texture_Boundaries(Top_Y, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);

						int vertical_x1 = Texture_Boundaries(Left_X, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int vertical_y1 = Texture_Boundaries(Left_Y, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int vertical_x2 = Texture_Boundaries(Right_X, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						int vertical_y2 = Texture_Boundaries(Right_Y, element->get_mPosX(), element->get_mPosY(), element->get_mAlpha(), gEnemyTexture);
						
						//system("cls");
						std::cout << element->get_mAlpha() << std::endl;
						if (std::tan(element->get_mAlpha() * M_PI / 180) != INFINITY) {
							std::cout << std::tan(element->get_mAlpha() * M_PI / 180) << std::endl;
						}

					    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
						SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
						SDL_RenderDrawLine(gRenderer, vertical_x1, vertical_y1, vertical_x2, vertical_y2);
/*_________________________________________________________________________________________*/
					}
				}
			}

			planet.render(gPlanetTexture);

			//Render objects
			SpaceCraft.render(gRenderer, gSpaceCraftTexture);
		
			if (showAccVector) {
				acceleration.render(gRenderer, gSpaceCraftTexture, gPlanetTexture, SpaceCraft, planet);
			} 
			
			//SpaceCraft.renderAccDirection(gRenderer);
		
/*_______________________________________________________________________________________________________*/
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
/*_________________________________________________________________________________________________________*/
			//destroy Enemy when collision detected
			if (!Enemies.empty()) {
				for (auto& element : Enemies) {

					if (element != nullptr) {
						int x, y = 0;
						x = element->get_mPosX() + gEnemyTexture.getCenterX();
						y = element->get_mPosY() + gEnemyTexture.getCenterY();

					//collision detection Enemey with Planet
						if (x < (SCREEN_WIDTH / 2 + 50) && x >(SCREEN_WIDTH / 2 - 50) && y < SCREEN_HEIGHT / 2 + 50 && y > SCREEN_HEIGHT / 2 - 50) {
							element->set_collision_detected();
						}

						
						if(element->get_exploded()){
							element.reset();
							cnt_Enemies--;
							Enemy_just_destroyed = true;
							spawning_delay -= 10;
							
							
							//increase Enemies spwaning at once after 10 destroyed Enemies
							if (++Enemies_destroyed % 10 == 0 && Enemies_destroyed != 0) {
								Enemies_at_once++;
								spawning_delay = 100;
							}
							std::cout << "Enemies destroyed: " << Enemies_destroyed << std::endl;
							std::cout << "spawning_delay: " << spawning_delay << std::endl;
							std::cout << "Enemies at once: " << Enemies_at_once << std::endl;
						}
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
