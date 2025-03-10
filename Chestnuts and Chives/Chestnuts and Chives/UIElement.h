#pragma once
#include <SDL3/SDL.h>
#include "Renderer.h"
class UIElement
{
private:
protected:
	int topLeftX;
	int topLeftY;
	int width;
	int height;
public:
	UIElement(int x, int y, int width, int height);
	virtual void Render(Renderer* renderer) = 0;
};

