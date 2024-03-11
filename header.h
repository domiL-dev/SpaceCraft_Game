#pragma once
#include <SDL.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <array>
#include <vector>
#include <memory>

//Screen dimension constants
static int SCREEN_WIDTH = 1200;//832;//640;
static int SCREEN_HEIGHT = 900;//624;//480;


//LaserShot length
static int LaserShot_length = 5;

const double G = 6.674 * pow(10, -11);

//length faktor vor Visualizing Acceleration Vektors
const double AccLengthFaktor = 10.0;


// Declare extern variables
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;







