#pragma once
#include "GameState.h"
#include <stack>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ExtraSoupState.h"
#include <string>
#include "Renderer.h"
using namespace std;
class GameManager
{
private:
	stack<GameState*> gameStates;
	Renderer* renderer;
	int ticks;
	bool initialized;
public:
	GameManager(Renderer* renderer);
	void SwitchState(GameState* state);
	SDL_Texture* LoadTexture(string filePath);
	void Render();
	void Update();
	void Initialize();
};

