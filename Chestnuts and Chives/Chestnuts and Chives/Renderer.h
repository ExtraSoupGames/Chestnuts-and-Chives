#pragma once
#include "SDL3/SDL.h"
#include <string>
#include <iostream>
#include <SDL3/SDL_render.h>
using namespace std;
enum ScreenResolutions {
	RES_None,
	RES_320X180,
	RES_640x360,
	RES_960X540,
	RES_1280X720,
	RES_1600X900,
	RES_1920X1080,
	RES_2240X1260,
	RES_2560X1540

};
class Renderer
{
private:
	ScreenResolutions resolution;
	SDL_Renderer* renderer;
	SDL_Window* window;
public:
	Renderer(string windowName);
	SDL_Texture* LoadTextureFromSurface(SDL_Surface* surface);
	void UpdateScreen();
	void FillBackground(SDL_Color* color);
	void DrawTexture(SDL_Texture* texture, int x, int y, int width, int height, float opacity = 1);
};

