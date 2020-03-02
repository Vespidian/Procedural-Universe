#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "data.h"
#include "DataTypes.h"
#include "initialize.h"

//SDL DEFINITIONS
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

int WIDTH = 800;
int HEIGHT = 800;
bool success = true;

bool init(){
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Random!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	return success;
}

void Quit() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}