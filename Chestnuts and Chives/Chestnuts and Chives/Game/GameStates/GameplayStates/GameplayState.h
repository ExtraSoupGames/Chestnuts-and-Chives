#pragma once
#include "Renderer.h"
#include "GameManager.h"
#include "NetworkUtilities.h"
class GameplayState {
private:
protected:
	GameManager* gameManager = nullptr;
public:
	virtual ~GameplayState() = default;
	virtual void Render(Renderer* renderer) = 0;
	virtual void Update(int frameTime) = 0;
	virtual void Initialize(GameManager* manager);
	virtual void ManageInput(SDL_Event* e) = 0;
	virtual void ProcessServerMessage(NetworkMessage* msg) = 0;
	virtual string GetStateCode() = 0;
};