#include "Math_Functions.h"

//int x, y = Position Coords of Texture,
// double Orientation is the rotated Orientation of Texture in degree
// LTexture Object is needed to get the width and height of Texture to calculate CenterCoords and Boundarie Coords
//Imagine a Cross wich goes through the CenterCoords with Top of the Cross as top of Spacecraft and Left,Right Bottom
//Function returns Top_X(0), Top_Y(1), Bottom_X(2), Bottom_Y(3), Right_X(4), Right_Y(5), Left_X(6), Left_Y(7)
int Texture_Boundaries(enum Output_Texture_Boundary value, int x, int y, double Orientation, LTexture& Texture) {
	int return_value; // lokal var -> retunr value

	/*inside switch case statements*/

	 Eigen::Vector2d Vector;                              //Create Vector Object to conatain Vector Coords
	//
	Eigen::Rotation2D<double> rotation_Matrix;			  //Create Rotation Matrix to transform Vector Coords
	//
	rotation_Matrix.angle() = Orientation * M_PI / 180;   //initialize rotation Matrix
	
	switch (value) {
	case Top_X:

		Vector = { 0,Texture.getHeight() / 2 }; //initialize with Coords Vector showing Upwards to Top Boundary
		Vector = rotation_Matrix*Vector;
		return  x + Texture.getCenterX()+Vector.x();
		break;

	case Top_Y:

		Vector = { 0,Texture.getHeight() / 2 }; //initialize with Coords Vector showing Up to Top Boundary
		Vector = rotation_Matrix * Vector;
		return  y + Texture.getCenterY() + Vector.y();
		break;
	case Bottom_X:
		Vector = { 0,-Texture.getHeight() / 2 }; //initialize with Coords Vector showing Down to Bottom Boundary
		Vector = rotation_Matrix * Vector;
		return  x + Texture.getCenterX() + Vector.x();
		break;

	case Bottom_Y:
		Vector = { 0,-Texture.getHeight() / 2 }; //initialize with Coords Vector showing Upwards to Top Boundary
		Vector = rotation_Matrix * Vector;
		return  y + Texture.getCenterY() + Vector.y();
		break;

	case Right_X:
		Vector = { Texture.getWidth()/2, 0}; //initialize with Coords Vector showing Right to Right Boundary
		Vector = rotation_Matrix * Vector;
		return  x + Texture.getCenterX() + Vector.x();
		break;

	case Right_Y:

		Vector = { Texture.getWidth() / 2, 0 }; //initialize with Coords Vector showing Right to Right Boundary
		Vector = rotation_Matrix * Vector;
		return  y + Texture.getCenterY() + Vector.y();
		break;

	case Left_X:

		Vector = { -Texture.getWidth() / 2, 0 }; //initialize with Coords Vector showing Left to Left Boundary
		Vector = rotation_Matrix * Vector;
		return  x + Texture.getCenterX() + Vector.x();
		break;
	case Left_Y:

		Vector = { -Texture.getWidth() / 2, 0 }; //initialize with Coords Vector showing Left to Left Boundary
		Vector = rotation_Matrix * Vector;
		return  y + Texture.getCenterY() + Vector.y();
		break;
	}



	//x += Texture.getCenterX(); //-> x = CenterCoords of Texture
	//y += Texture.getCenterY(); //-> y = CenterCoords of Texture

	//exture_Boundaries[0] = mAplpha §

}