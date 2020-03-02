#include <math.h>
#include <SDL2/SDL.h>
#include "initialize.h"
#include "DataTypes.h"
#include "data.h"

void DrawCircle(SDL_Renderer *renderer, int x, int y, float radius){
	if(x <= WIDTH && y <= HEIGHT){
		int numOfVertices = 360 + 1;
		float doublePi = 2.0f * M_PI;
		
		Vector2 circleVertices[numOfVertices];
		circleVertices[0] = (Vector2){x, y};
		
		for(int i = 1; i < numOfVertices; i++){
			circleVertices[i].x = x + (radius * cos(i * doublePi / 360));
			circleVertices[i].y = y + (radius * sin(i * doublePi / 360));
		}
		for(int i = 0; i < numOfVertices-1; i++){
			SDL_RenderDrawLine(renderer, circleVertices[i].x, circleVertices[i].y, circleVertices[i+1].x, circleVertices[i+1].y);
		}
		SDL_RenderDrawLine(renderer, circleVertices[1].x, circleVertices[1].y, circleVertices[numOfVertices-1].x, circleVertices[numOfVertices-1].y);
	}
}