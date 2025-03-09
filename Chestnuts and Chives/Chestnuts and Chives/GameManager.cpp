#include "GameManager.h"

GameManager::GameManager(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
	ticks = 0;
}

void GameManager::SwitchState(GameState* state)
{
	gameStates.push(state);
}

SDL_Texture* GameManager::LoadTexture(string filePath)
{
	filePath = string(SDL_GetBasePath()) + filePath;
	SDL_IOStream* fileStream = SDL_IOFromFile(filePath.c_str(), "r");
	if (fileStream == NULL) {
		cout << "Error opening file" << SDL_GetError();
	}
	SDL_Surface* surface = IMG_LoadPNG_IO(fileStream);
	if (surface == NULL) {
		cout << "Error creating surface" << SDL_GetError();
	}

	SDL_Texture* texture =  renderer->LoadTextureFromSurface(surface);

	SDL_DestroySurface(surface);
	SDL_CloseIO(fileStream);
	return texture;
}

void GameManager::Render()
{
	if (!initialized) {
		return;
	}
	gameStates.top()->Render(renderer);
}

void GameManager::Update()
{
	if (!initialized) {
		return;
	}
	int frameTimeMillis = SDL_GetTicks() - ticks;
	ticks = SDL_GetTicks();
	gameStates.top()->Update(frameTimeMillis);
}

void GameManager::Initialize()
{
	initialized = true;
	SwitchState(new ExtraSoupState());
	gameStates.top()->Initialize(this);
	ticks = SDL_GetTicks();
}
