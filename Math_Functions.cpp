#include "Math_Functions.h"
#include <iostream>

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
}


// point_within_area determines whether a point is inside a area of a parallelogram -> details for equation see Notion or attached pdf in GitHub
bool point_within_area(int& P_x, int& P_y, int& A_x, int& A_y, int& B_x, int& B_y, int& D_x, int& D_y ) {
	if (B_x == A_x || D_y == A_y) {
		return false;
	}
	double a = (P_x - A_x) / (B_x - A_x);
	double b = (D_x - A_x) / (B_x - A_x);
	double c = (P_y - A_y) / (D_y - A_y);
	double d = (B_y - A_y) / (D_y - A_y);

	double s = (c - a * d) / (1 - b * d);
	double r = a - b * (c - a * d) / (1 - b * d);

	

	if (r > 0.0 && r < 1.0 && s > 0.0 && s < 1.0) {
		std::cout << "s = " << s << "| r = " << r << std::endl;
		return true;
	}
	else {
		
		return false;
	}
}