#include "ExtraSoupState.h"

ExtraSoupState::ExtraSoupState()
{
	fadeInTimer = 0;
	fadeInDuration = 300;

	sustainTimer = 0;
	sustainDuration = 1000;

	fadeOutTimer = 0;
	fadeOutDuration = 300;

	finalDelayTimer = 0;
	finalDelayDuration = 500;

	fadingState = None;

	backgroundColor = new SDL_Color{ 0, 149, 233, 255 };

	//assigned at initialization
	logoTexture = nullptr;
	gameManager = nullptr;
}

ExtraSoupState::~ExtraSoupState()
{
	delete backgroundColor;
	delete logoTexture;
}

void ExtraSoupState::Update(int frameTime)
{
	switch (fadingState) {
	case FadingIn:
		fadeInTimer += frameTime;
		if (fadeInTimer > fadeInDuration) {
			fadingState = Sustaining;
		}
		break;
	case Sustaining:
		sustainTimer += frameTime;
		if (sustainTimer > sustainDuration) {
			fadingState = FadingOut;
		}
		break;
	case FadingOut:
		fadeOutTimer += frameTime;
		if (fadeOutTimer > fadeOutDuration) {
			fadingState = FinalDelay;
		}
		break;
	case FinalDelay:
		finalDelayTimer += frameTime;
		if (finalDelayTimer > finalDelayDuration) {
			gameManager->SwitchState(new TestUI());
		}
	}
}
void ExtraSoupState::Render(Renderer* renderer)
{
	renderer->FillBackground(backgroundColor);
	float opacity;
	switch (fadingState) {
	case FadingIn:
		opacity = (float)fadeInTimer / (float)fadeInDuration;
		//clamp the opacity between 1 and 0
		opacity = opacity < 0 ? 0 : opacity > 1 ? 1 : opacity;
		cout << "opcaity should be: " << opacity << endl;
		renderer->DrawTexture(logoTexture, 148, 78, opacity);
		break;
	case Sustaining:
		opacity = 1;
		renderer->DrawTexture(logoTexture, 148, 78, opacity);
		break;
	case FadingOut:
		opacity = (float)fadeOutTimer / (float)fadeOutDuration;
		//clamp the opacity between 1 and 0
		opacity = opacity < 0 ? 0 : opacity > 1 ? 1 : opacity;
		//flip the opacity (fade out not in)
		opacity = 1 - opacity;
		renderer->DrawTexture(logoTexture, 148, 78, opacity);
		break;
	case FinalDelay:
		renderer->FillBackground(backgroundColor);
		renderer->UpdateScreen();
		break;
	}
	renderer->UpdateScreen();
}

void ExtraSoupState::Initialize(GameManager* manager)
{
	gameManager = manager;
	logoTexture = manager->LoadTexture("Soup.png");
	fadingState = FadingIn;
}

void ExtraSoupState::Pause()
{
}

void ExtraSoupState::Resume()
{
}

void ExtraSoupState::Exit()
{
}
