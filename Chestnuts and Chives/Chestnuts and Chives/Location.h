#pragma once
#include <string>
#include "SDL3/SDL.h"
#include "Renderer.h"
using namespace std;
class Location
{
	SDL_Texture* locationTexture;
	string locationName;
public:
	void Render(Renderer* renderer);
};

