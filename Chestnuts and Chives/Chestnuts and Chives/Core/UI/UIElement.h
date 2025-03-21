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
	// blocking elements may not overlap
	// a UI screen should be built of 1 layer of blocking elements
	// with non blocking elements on top
	bool isBlocking;
	// determines wether this UI Element can be clicked
	// if false clicks will pass through onto ui elements underneath
	bool isClickable;
	//TODO implement functionality for these, most likely in UIState
public:
	UIElement(int x, int y, int width, int height);
	virtual void Render(Renderer* renderer) = 0;
	virtual void HoverStarted() = 0;
	virtual void HoverEnded() = 0;
	virtual void Clicked() = 0;
	bool ContainsMouse(int mouseX, int mouseY);
	bool hovered;
};

