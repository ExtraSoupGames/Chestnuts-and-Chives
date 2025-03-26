#include "AssetLoader.h"

float AssetLoader::LoadNextTexture(Renderer* renderer)
{
	if (textureNum >= textureNames.size()) {
		return -1;
	}
	string textureName = textureNames[textureNum];
	SDL_Texture* newTexture = LoadTexture(textureName, renderer);
	textures->AddItem(textureName, newTexture);
	textureNum++;
	return (float)textureNum / (float)textureNames.size();
}


AssetLoader::AssetLoader()
{
	textures = make_unique<AssetDictionary<SDL_Texture*>>();
	textureNum = 0;
}
AssetLoader::~AssetLoader() {
}
unique_ptr<AssetDictionary<SDL_Texture*>> AssetLoader::GetTextures()
{
	return move(textures);
}
SDL_Texture* AssetLoader::LoadTexture(string filePath, Renderer* renderer)
{
	filePath = string(SDL_GetBasePath()) + "Assets/Textures/" + filePath + ".png";
	SDL_IOStream* fileStream = SDL_IOFromFile(filePath.c_str(), "r");
	if (fileStream == NULL) {
		cout << "Error opening file" << SDL_GetError();
	}
	SDL_Surface* surface = IMG_LoadPNG_IO(fileStream);
	if (surface == NULL) {
		cout << "Error creating surface" << SDL_GetError();
	}

	SDL_Texture* texture = renderer->LoadTextureFromSurface(surface);

	SDL_DestroySurface(surface);
	SDL_CloseIO(fileStream);
	return texture;
}
