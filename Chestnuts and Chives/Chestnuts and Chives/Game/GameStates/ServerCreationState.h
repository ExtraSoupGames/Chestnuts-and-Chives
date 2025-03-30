#pragma once
#include "GameState.h"
#include "ConnectingState.h"
class ServerCreationState : public GameState {
public:
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(Client* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
};