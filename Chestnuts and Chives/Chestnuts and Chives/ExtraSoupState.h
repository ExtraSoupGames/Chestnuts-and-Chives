#pragma once
#include "GameState.h"
#include <algorithm>
#include "TestUI.h"
#include "GameManager.h"
#include <iostream>
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
	GameManager* gameManager;
public:
	ExtraSoupState();
	~ExtraSoupState();

	virtual void Update(int frameTime) override;
	virtual void Render(Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Exit() override;
};