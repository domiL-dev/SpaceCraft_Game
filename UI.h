#pragma once

#include "header.h"
#include "LTexture.h"
#include <SDL.h>
class UI
{	
public:
	//initialize UI Data
	UI(SDL_Renderer* renderer);

	//frees UI Data
	~UI();

	//render health bar
	void render_health_bar(Uint8 health);

	//render Enemies Destroyed Counter
	void render_cnt_Enemies_Destroyed(LTexture& gEnemies_Destroyed_Texture, std::vector<LTexture>& gDigits_Texture);

	//increment Enemies Destroyed Counter
	void increment_cnt_Enemies_Destroyed();

	//reset Enemies Destroyed Counter(;
	void reset_cnt_Enemies_Destroyed();

private:

	SDL_Renderer* m_renderer;

	/*Data to visualize Game Progress during playing*/
	int cnt_Enemies_Destroyed; 

	//Position Coords for texture
	int posX_Enemies_Destroyed_Texture, posX_tens, posX_ones;

	//Position Y-Coords of Line
	int posY;

	//varible to store numbers with multiple digits in seperate digits
	int tens, ones;

	//flags for logic of rendering numbers with multiple digits
	bool firstTime_in_ones, firstTime_in_tens;

	
	const SDL_Rect* health_bar;

	/*______________________________________________*/

};

