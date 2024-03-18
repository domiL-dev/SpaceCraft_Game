#include "UI.h"

#include <iostream>


UI::UI(SDL_Renderer* renderer) : m_renderer{renderer},
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
void UI::render_cnt_Enemies_Destroyed(LTexture& gEnemies_Destroyed_Texture, std::vector<LTexture>& gDigits_Texture) {

	gEnemies_Destroyed_Texture.render(posX_Enemies_Destroyed_Texture, posY);

	if (cnt_Enemies_Destroyed < 10 ) {

		if (firstTime_in_ones) {
			posX_ones = posX_Enemies_Destroyed_Texture + gEnemies_Destroyed_Texture.getWidth();
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
