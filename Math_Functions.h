#pragma once

#include <cmath>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Geometry> 
#include "header.h"
#include "LTexture.h"
#include "Enemy.h"

//Enumeration list to select output for the Function Texture_Boundaries
enum Output_Texture_Boundary { Top_X, Top_Y, Bottom_X, Bottom_Y, Right_X, Right_Y, Left_X, Left_Y };

//enum Output value = choosing wich Coords will be returned
//int x, y = Position Coords of Texture,
// double Orientation = the rotated Orientation of Texture in degree
// LTexture Object is needed to get the width and height of Texture to calculate CenterCoords and Boundarie Coords
//Imagine a Cross wich goes through the CenterCoords with Top of the Cross as top of Spacecraft and Left,Right Bottom
//Function returns value dependend on Output -> Top_X = 0, Top_Y=1, Bottom_X=2, Bottom_Y=3, Right_X=4, Right_Y=5, Left_X=6, Left_Y=7
int Texture_Boundaries(enum Output_Texture_Boundary value, int x, int y, double Orientation, LTexture& Texture);


//determine whether the point lies within the area -> returns true or false
//int x, y = point Coords wich will be tested
//Objects of Type Enemy and LTexture neccessary to determine the area for collision detection 
bool point_within_area(int x, int y, int A_x, int A_y, int B_x, int B_y, int D_x, int D_y);
