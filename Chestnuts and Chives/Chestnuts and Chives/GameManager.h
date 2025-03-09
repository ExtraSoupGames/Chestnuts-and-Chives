#pragma once
#include "GameState.h"
#include <stack>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ExtraSoupState.h"
#include <string>
using namespace std;
class GameManager
{
private:
	stack<GameState*> gameStates;
	SDL_Renderer* renderer;
	int ticks;
	bool initialized;
public:
	GameManager(SDL_Renderer* renderer);
	void SwitchState(GameState* state);
	SDL_Texture* LoadTexture(string filePath);
	void Render();
	void Update();
	void Initialize();
};

