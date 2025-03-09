#pragma once
#include "Renderable.h"
#include "Renderer.h"
class UIElement : public Renderable
{
private:
	int topLeftX;
	int topLeftY;
	int width;
	int height;
public:
	void Render(Renderer* renderer);
	UIElement(SDL_Texture* texture, int x, int y, int width, int height);
};

