#pragma once
#include "UIGameplayState.h"
#include "NetworkUtilities.h"
#include "SDL3/SDL.h"
class TestGameplayState : public UIGameplayState {
private:
	bool playerHasVoted;
protected:
public:
	TestGameplayState();
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(Client* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
	virtual string GetStateCode() override;
};