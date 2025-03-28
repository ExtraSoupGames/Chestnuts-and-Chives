#include "ExtraSoupState.h"
#include "ConnectedState.h"
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
			gameManager->SwitchState(new ConnectedState());
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
		renderer->DrawTexture(logoTexture, 148, 78, 32, 32, opacity);
		break;
	case Sustaining:
		opacity = 1;
		renderer->DrawTexture(logoTexture, 148, 78, 32, 32, opacity);
		break;
	case FadingOut:
		opacity = (float)fadeOutTimer / (float)fadeOutDuration;
		//clamp the opacity between 1 and 0
		opacity = opacity < 0 ? 0 : opacity > 1 ? 1 : opacity;
		//flip the opacity (fade out not in)
		opacity = 1 - opacity;
		renderer->DrawTexture(logoTexture, 148, 78, 32, 32, opacity);
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
	logoTexture = manager->GetTexture("Soup");
	fadingState = FadingIn;
}
void ExtraSoupState::ManageInput(SDL_Event* e) {

}

void ExtraSoupState::ProcessServerMessage(NetworkMessage* msg)
{
}
