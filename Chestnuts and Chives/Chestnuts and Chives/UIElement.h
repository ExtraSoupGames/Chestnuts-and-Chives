#pragma once
#include "Renderable.h"
class UIElement : Renderable
{
private:
	int topLeftX;
	int topLeftY;
public:
	void Render(SDL_Renderer* renderer);
	UIElement(SDL_Texture* texture, int x, int y);
};

