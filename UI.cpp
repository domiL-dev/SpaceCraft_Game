#include "UI.h"

#include <iostream>


UI::UI() : m_renderer{NULL}, m_window{NULL},
		  cnt_Enemies_Destroyed{ 0 }, health_bar{NULL},
		  posX_Enemies_Destroyed_Texture{ 30 }, posY{ 30 },
		  posX_tens{ 0} , 
		  posX_ones{ 0 },
	      tens{ 0 }, ones{ 0 },
		  firstTime_in_ones{ true }, firstTime_in_tens{ true}
{

}

UI::~UI() {

}

//render health bar
void UI::render_health_bar(Uint8 health) {
	SDL_Rect bar{ 800, 800, health, 10, };
	health_bar = &bar;
	SDL_SetRenderDrawColor(this->m_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(this->m_renderer, health_bar);
}

//render Enemies Destroyed Counter
void UI::render_cnt_Enemies_Destroyed(LTexture& Enemies_Destroyed_Text_Texture, std::vector<LTexture>& gDigits_Texture) {

	Enemies_Destroyed_Text_Texture.render(posX_Enemies_Destroyed_Texture, posY);

	if (cnt_Enemies_Destroyed < 10 ) {

		if (firstTime_in_ones) {
			posX_ones = posX_Enemies_Destroyed_Texture + Enemies_Destroyed_Text_Texture.getWidth();
			firstTime_in_ones = false;
		}
		gDigits_Texture[cnt_Enemies_Destroyed].render(posX_ones, posY);

	}
	else if (cnt_Enemies_Destroyed >= 10 && cnt_Enemies_Destroyed < 100) {

		if (firstTime_in_tens) {
			posX_tens = posX_ones;
			posX_ones += gDigits_Texture[8].getWidth();
			firstTime_in_tens = false;

		}


		tens = static_cast<int>(cnt_Enemies_Destroyed / 10);

		gDigits_Texture[tens].render(posX_tens, posY);

		ones = cnt_Enemies_Destroyed % 10;

		gDigits_Texture[ones].render(posX_ones, posY);
	}

}

//increment Enemies Destroyed Counter
void UI::increment_cnt_Enemies_Destroyed(){
	cnt_Enemies_Destroyed++;
}


//reset Enemies Destroyed Counter(;
void UI::reset_cnt_Enemies_Destroyed() {

	cnt_Enemies_Destroyed = 0;
}

bool UI::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	//Initialize SDL_tff
	else if (TTF_Init()) {
		printf("SDL tff could not initialize! SDL Error: %s\n", SDL_GetError());
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
		m_window = SDL_CreateWindow("SpaceCraft_Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

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


SDL_Renderer* UI::get_m_renderer() {
	return m_renderer;
}

SDL_Window* UI::get_m_window() {
	return m_window;
}



