#include "GameManager.h"
GameManager::GameManager(Renderer* renderer)
{
	this->renderer = renderer;
	initialized = false;
	ticks = 0;
	gameState = nullptr;
}

void GameManager::SwitchState(GameState* state)
{
	delete gameState;
	gameState = state;
	state->Initialize(this);
}

SDL_Texture* GameManager::GetTexture(string textureName)
{
	SDL_Texture* texture = textures.GetItem(textureName);
	if (texture == nullptr) {
		cout << "Returned null texture, texture with name: " << textureName << " wasnt loaded correctly" << endl;
	}
	return textures.GetItem(textureName);
}

void GameManager::Render()
{
	if (!initialized) {
		return;
	}
	gameState->Render(renderer);
}

void GameManager::Update()
{
	if (!initialized) {
		return;
	}
	int frameTimeMillis = SDL_GetTicks() - ticks;
	ticks = SDL_GetTicks();
	gameState->Update(frameTimeMillis);
}

void GameManager::Initialize()
{
	if (initialized) {
		cout << "Game Manager initialize requested, but manager is already initialized" << endl;
		return;
	}
	initialized = true;
	SwitchState(new AssetLoadingState());
	ticks = SDL_GetTicks();
}

void GameManager::ManageInput(SDL_Event* e)
{
	if (!initialized) {
		return;
	}
	gameState->ManageInput(e);
}

void GameManager::TexturesLoaded(AssetDictionary<SDL_Texture*>* textureDict)
{
	textures = *textureDict;
}
