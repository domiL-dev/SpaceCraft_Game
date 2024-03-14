#pragma once

#include "header.h"
#include "LTexture.h"
class UI
{	
public:
	//initialize UI Data
	UI();

	//frees UI Data
	~UI();

	//render Enemies Destroyed Counter
	void render_cnt_Enemies_Destroyed(LTexture& gEnemies_Destroyed_Texture, std::vector<LTexture>& gDigits_Texture);

	//increment Enemies Destroyed Counter
	void increment_cnt_Enemies_Destroyed();

	//reset Enemies Destroyed Counter(;
	void reset_cnt_Enemies_Destroyed();

private:

	/*Data to visualize Game Progress during playing*/
	int cnt_Enemies_Destroyed; 

	//Position Coords for texture
	int posX_Enemies_Destroyed_Texture, posX_tens, posX_ones;

	//Position Y-Coords of Line
	int posY;

	//varible to store numbers with multiple digits in seperate digits
	int tens, ones;

	bool firstTime_in_ones, firstTime_in_tens;

	/*______________________________________________*/

};

