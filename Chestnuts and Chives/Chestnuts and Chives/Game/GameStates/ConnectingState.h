#pragma once
#include "GameState.h"

class ConnectingState : public GameState {
public:
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
};