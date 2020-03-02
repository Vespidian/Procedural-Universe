#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stddef.h>

#include <SDL2/SDL.h>
#include "data.h"
#include "DataTypes.h"
#include "drawFunctions.h"
#include "initialize.h"
// Normally SDL2 will redefine the main entry point of the program for Windows applications
// this doesn't seem to play nice with TCC, so we just undefine the redefinition
#ifdef __TINYC__
    #undef main
#endif

//FUNCTION PREDEFINITIONS
bool init();
void RenderScreen();
void drawCircle(int xc, int yc, int x, int y);
void circleBres(int xc, int yc, int r);

int worldSeed = 100;

const int numOfSectors = 16;

int sectorsX;
int sectorsY;

bool pointExists = false;

Vector2 galaxyOffset = {0, 0};
Vector2 mousePos = {0, 0};
char alphaNum[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


void clearScreen(){
	// SDL_SetRenderDrawColor(gRenderer, 201, 188, 141, 0xff);
	SDL_SetRenderDrawColor(gRenderer, 2, 2, 2, 0xff);
	SDL_RenderClear(gRenderer);
}
//MISC
bool quit = false;
SDL_Event e;
static const int targetFramerate = 60;

int main(int argc, char **argv) {
	init();
	if(init){
		sectorsX = WIDTH / numOfSectors;
		sectorsY = HEIGHT / numOfSectors;
		time_t start_t, end_t;
		double diff_t;
		while(!quit){
		RenderScreen();
			time(&start_t);
			//DRAW TO SCREEN			
			
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if(currentKeyStates[SDL_SCANCODE_ESCAPE]){
				quit = true;
			}
			if(currentKeyStates[SDL_SCANCODE_W]){
				galaxyOffset.y -= 1;
				RenderScreen();
			}
			if(currentKeyStates[SDL_SCANCODE_S]){
				galaxyOffset.y += 1;
				RenderScreen();
			}
			if(currentKeyStates[SDL_SCANCODE_A]){
				galaxyOffset.x -= 1;
				RenderScreen();
			}
			if(currentKeyStates[SDL_SCANCODE_D]){
				galaxyOffset.x += 1;
				RenderScreen();
			}
			// if(currentKeyStates[SDL_SCANCODE_COMMA]){
				// WIDTH -= 1;
				// SDL_SetWindowSize(gWindow, WIDTH, HEIGHT);
			// }
			// if(currentKeyStates[SDL_SCANCODE_PERIOD]){
				// WIDTH += 1;
				// SDL_SetWindowSize(gWindow, WIDTH, HEIGHT);
			// }
			SDL_Delay(10);
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_KEYDOWN){
					if(e.key.keysym.sym == SDLK_r){
						printf("x: %d | y: %d\n", galaxyOffset.x, galaxyOffset.y);
					}else if(e.key.keysym.sym == SDLK_c){
						system("@cls||clear");
					}
					// else if(e.key.keysym.sym == SDLK_w){
						// galaxyOffset.y -= 1;
						// RenderScreen();
					// }else if(e.key.keysym.sym == SDLK_s){
						// galaxyOffset.y += 1;
						// RenderScreen();
					// }else if(e.key.keysym.sym == SDLK_a){
						// galaxyOffset.x -= 1;
						// RenderScreen();
					// }else if(e.key.keysym.sym == SDLK_d){
						// galaxyOffset.x += 1;
						// RenderScreen();
					// }
				}else if(e.type == SDL_MOUSEBUTTONDOWN){
					if(e.button.button == SDL_BUTTON_LEFT){
						// printf("hideho neighbour");
						SDL_GetMouseState(&mousePos.x, &mousePos.y);
						nLehmer = ((((mousePos.x/numOfSectors) & 0xFFFF) + galaxyOffset.x << 16 | ((mousePos.y / numOfSectors) & 0xFFFF)) + galaxyOffset.y) + worldSeed;
						if(getRnd(0, 50) == 1){
							Star tmpStar;
							tmpStar.size = getRnd(2, 8);
							// printf("STAR!!!!");
							//char starNum[3];
							char buffer[3];

							for(int i = 0; i <= 5; i++){
								if(i <= 1){
									tmpStar.name[i] = alphaNum[getRnd(0, 25)];
								}else if(i == 2){
									tmpStar.name[i] = '-';
								}else{
									itoa(getRnd(0, 9), buffer, 10);
									tmpStar.name[i] = buffer[i - 3];
									//itoa(getRnd(100, 999), starNum, 10);
									//strcat(&tmpStar.name[i], &starNum[i - 3]);
								}
							} 
							printf("+++ Star %s +++\n", tmpStar.name);
							printf("Position: \n -> x: %d | y: %d\n", galaxyOffset.x + (mousePos.x / numOfSectors), galaxyOffset.y + (mousePos.y / numOfSectors));
							printf("Size: \n -> %d\n", tmpStar.size);
							printf("+++++++++++++++++\n");
						}
					}
				}else if(e.type == SDL_QUIT){
					quit = true;
				}
			}
			//Game FrameRate
			SDL_Delay(1000 / targetFramerate);
		}
	}else{
		printf("Failed to initialize\n");
	}
	if(quit){
		Quit();
	}
}

void RenderScreen(){
	clearScreen();
	
	// SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xff);
	// circleBres(400, 400, 300);
	
	for(int y = 0; y < sectorsY; y++){
		for(int x = 0; x < sectorsX; x++){
			SDL_SetRenderDrawColor(gRenderer, getRnd(0, 255),getRnd(0, 255),getRnd(0, 255), 0xff);
			nLehmer = (((x & 0xFFFF) + galaxyOffset.x << 16 | (y & 0xFFFF)) + galaxyOffset.y) + worldSeed;
			//nLehmer = x * y;
			pointExists = (getRnd(0, 50) == 1);
			//printf("%d",getRnd(0, 10));
			if(pointExists){
				Star tmpStar;
				tmpStar.size = getRnd(2, 8);
				// DrawCircle(gRenderer, x * numOfSectors + numOfSectors/2, y * numOfSectors + numOfSectors/2, getRnd(4, 20));
				circleBres((x * numOfSectors + numOfSectors/2), (y * numOfSectors + numOfSectors/2), tmpStar.size);
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				if(mousePos.x/numOfSectors == x && mousePos.y/numOfSectors == y){					
					SDL_SetRenderDrawColor(gRenderer, 255, 204, 0, 0xff);
					circleBres((x * 16) + 8, (y * 16) + 8, tmpStar.size + 4);
				}
			}
		}
	}
	SDL_RenderPresent(gRenderer);
}


  
// Function for circle-generation 
// using Bresenham's algorithm 
void circleBres(int xc, int yc, int r)
{ 
    int x = 0, y = r;
    int d = 3 - 2 * r;
    SDL_RenderDrawPoint(gRenderer, xc+x, yc+y);
    SDL_RenderDrawPoint(gRenderer, xc-x, yc+y);
    SDL_RenderDrawPoint(gRenderer, xc+x, yc-y);
    SDL_RenderDrawPoint(gRenderer, xc-x, yc-y);
    SDL_RenderDrawPoint(gRenderer, xc+y, yc+x);
    SDL_RenderDrawPoint(gRenderer, xc-y, yc+x);
    SDL_RenderDrawPoint(gRenderer, xc+y, yc-x);
    SDL_RenderDrawPoint(gRenderer, xc-y, yc-x);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels 
        x++;
        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        SDL_RenderDrawPoint(gRenderer, xc+x, yc+y);
		SDL_RenderDrawPoint(gRenderer, xc-x, yc+y);
		SDL_RenderDrawPoint(gRenderer, xc+x, yc-y);
		SDL_RenderDrawPoint(gRenderer, xc-x, yc-y);
		SDL_RenderDrawPoint(gRenderer, xc+y, yc+x);
		SDL_RenderDrawPoint(gRenderer, xc-y, yc+x);
		SDL_RenderDrawPoint(gRenderer, xc+y, yc-x);
		SDL_RenderDrawPoint(gRenderer, xc-y, yc-x);
        //delay(50); 
    } 
}