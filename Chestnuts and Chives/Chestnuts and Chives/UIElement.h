#pragma once
#include "Renderable.h"
#include "Renderer.h"
class UIElement : Renderable
{
private:
	int topLeftX;
	int topLeftY;
public:
	void Render(Renderer* renderer);
	UIElement(SDL_Texture* texture, int x, int y);
};

