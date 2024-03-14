#include "UI.h"


UI::UI() :cnt_Enemies_Destroyed{ 0 }, 
		  posX_Enemies_Destroyed_Texture{ 30 }, posY{ 30 },
		  posX_tens{ 0} , 
		  posX_ones{ 0 },
	      tens{ 0 }, ones{ 0 },
		  firstTime_in_ones{ true }, firstTime_in_tens{ true}
{

}

UI::~UI() {

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
