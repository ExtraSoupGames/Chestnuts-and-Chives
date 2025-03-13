#pragma once
#include "Location.h";
#include "GameManager.h"
#include "SDL3/SDL.h"
class Path
{
	Location* location1;
	Location* location2;
	int travelCost;
	SDL_Texture* pathTexture;
public:
	Path(GameManager* gameManager);
	void Render(Renderer* renderer, int mapX, int mapY, int mapWidth, int mapHeight, int offsetX, int offsetY);
};

