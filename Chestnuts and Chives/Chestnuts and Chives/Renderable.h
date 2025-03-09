#pragma once
#include <SDL3/SDL.h>
class Renderable
{
protected:
	SDL_Texture* texture;
	Renderable(SDL_Texture* texture);
public:
	virtual void Render(SDL_Renderer* renderer) = 0;
};

