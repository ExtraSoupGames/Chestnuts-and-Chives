#pragma once
#include <SDL3/SDL.h>
#include "Renderer.h"
class UIElement
{
private:
	int topLeftX;
	int topLeftY;
	int width;
	int height;
	SDL_Texture* texture;
public:
	void Render(Renderer* renderer);
	UIElement(SDL_Texture* texture, int x, int y, int width, int height);
};

