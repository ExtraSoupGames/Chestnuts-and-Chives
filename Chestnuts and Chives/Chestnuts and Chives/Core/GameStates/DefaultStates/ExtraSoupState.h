#pragma once
#include "GameState.h"
#include <algorithm>
#include <iostream>
#include "Client.h"
using namespace std;
class ExtraSoupState : public GameState
{
private:
	int fadeInTimer;
	int fadeInDuration;

	int sustainTimer;
	int sustainDuration;

	int fadeOutTimer;
	int fadeOutDuration;

	int finalDelayTimer;
	int finalDelayDuration;

	enum FadingState {
		None,
		FadingIn,
		Sustaining,
		FadingOut,
		FinalDelay
	};

	FadingState fadingState;
	SDL_Texture* logoTexture;
	SDL_Color* backgroundColor;
	Client* gameManager;
public:
	ExtraSoupState();
	virtual ~ExtraSoupState() override;

	virtual void Update(int frameTime) override;
	virtual void Render(Renderer* renderer) override;
	virtual void Initialize(Client* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
};