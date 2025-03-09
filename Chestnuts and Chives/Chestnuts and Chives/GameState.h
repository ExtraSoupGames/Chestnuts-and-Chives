#pragma once
#include "SDL3/SDL.h"
#include "Renderer.h"
//Forward declaration
class GameManager;

class GameState
{
public:
	virtual void Update(int frameTime) = 0;
	virtual void Render(Renderer* renderer) = 0;
	virtual void Initialize(GameManager* manager) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Exit() = 0;
};
class BaseGameState : GameState
{
public:

};

