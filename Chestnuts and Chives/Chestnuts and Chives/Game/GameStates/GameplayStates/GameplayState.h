#pragma once
#include "Renderer.h"
#include "NetworkUtilities.h"
#include "Client.h"
class GameplayState {
private:
protected:
	Client* gameManager = nullptr;
public:
	virtual ~GameplayState() = default;
	virtual void Render(Renderer* renderer) = 0;
	virtual void Update(int frameTime) = 0;
	virtual void Initialize(Client* manager);
	virtual void ManageInput(SDL_Event* e) = 0;
	virtual void ProcessServerMessage(NetworkMessage* msg) = 0;
	virtual string GetStateCode() = 0;
};