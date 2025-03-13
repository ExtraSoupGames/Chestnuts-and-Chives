#pragma once
#include <string>
#include "SDL3/SDL.h"
#include "Renderer.h"
using namespace std;
class GameManager;
class Location
{
	SDL_Texture* locationTexture;
	string locationName;
public:
	Location(GameManager* gameManager);
	void Render(Renderer* renderer, int mapX, int mapY, int mapWidth, int mapHeight, int offsetX, int offsetY);
};

