#pragma once
#include "GameState.h"
#include "Client.h"
class NonHostState : GameState
{
private:
	Client* client;
public:
	void Initialize(GameManager* gameManager) override;
};

