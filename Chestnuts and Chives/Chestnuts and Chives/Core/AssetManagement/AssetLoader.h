#pragma once
#include <unordered_map>
#include <string>
#include <array>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Renderer.h"
#include "AssetDictionary.h"
using namespace std;
//map wrapper to prevent accidentally adding items to the map

class AssetLoader
{
	array<string, 7> textureNames = {
		"Soup",
		"Map",
		"Paths",
		"Location",
		"UI/Left",
		"UI/Right",
		"UI/Middle"
	};
	int textureNum;
	AssetDictionary<SDL_Texture*> textures;
	SDL_Texture* LoadTexture(string filePath, Renderer* renderer);

public:
	AssetLoader();
	AssetDictionary<SDL_Texture*>* GetTextures();
	// returns the percent of textures loaded	
	float LoadNextTexture(Renderer* renderer);
};