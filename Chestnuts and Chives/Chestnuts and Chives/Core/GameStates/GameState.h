#pragma once
#include "SDL3/SDL.h"
#include "Renderer.h"
#include "NetworkUtilities.h"
#include "Client.h"
//Forward declaration
class GameManager;

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void Update(int frameTime) = 0;
	virtual void Render(Renderer* renderer) = 0;
	virtual void Initialize(Client* manager) = 0;
	virtual void ManageInput(SDL_Event* e) = 0;
	virtual void ProcessServerMessage(NetworkMessage* msg) = 0;
};
class BaseGameState : GameState
{
public:

};

