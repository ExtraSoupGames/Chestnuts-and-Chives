#pragma once
#include "Location.h";
#include "SDL3/SDL.h"
class Path
{
	Location* location1;
	Location* location2;
	int travelCost;
	SDL_Texture* pathTexture;
public:
	void Render(Renderer* renderer);
};

