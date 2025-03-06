#pragma once
#include "GameState.h"
#include "Server.h"
#include "Client.h"
class HostState : GameState
{
private:
	Client* client;
	Server* server;
public:
	void Initialize(GameManager* gameManager) override;
};

