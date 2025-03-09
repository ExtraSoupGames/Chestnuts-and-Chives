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
	float fadeInTimer;
	float fadeInDuration;

	float sustainTimer;
	float sustainDuration;

	float fadeOutTimer;
	float fadeOutDuration;

	enum FadingState {
		None,
		FadingIn,
		Sustaining,
		FadingOut
	};

	FadingState fadingState;
	SDL_Texture* logoTexture;
	SDL_Color* backgroundColor;
	GameManager* gameManager;
public:
	ExtraSoupState();
	~ExtraSoupState();

	virtual void Update(float frameTime) override;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Exit() override;
};