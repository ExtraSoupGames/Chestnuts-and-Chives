#pragma once
#include <string>
#include "SDL3/SDL.h"
#include "Renderer.h"
#include "Client.h"
using namespace std;
class GameManager;
class Location
{
	SDL_Texture* locationTexture;
	string locationName;
public:
	Location(Client* gameManager);
	void Render(Renderer* renderer, int mapX, int mapY, int mapWidth, int mapHeight, int offsetX, int offsetY);
};

