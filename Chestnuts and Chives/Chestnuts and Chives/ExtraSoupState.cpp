#include "ExtraSoupState.h"

ExtraSoupState::ExtraSoupState()
{
	fadeInTimer = 0;
	fadeInDuration = 300;

	sustainTimer = 0;
	sustainDuration = 1000;

	fadeOutTimer = 0;
	fadeOutDuration = 300;

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

void ExtraSoupState::Update(float frameTime)
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
			gameManager->SwitchState(new TestUI());
		}
		break;
	}
}
void ExtraSoupState::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, backgroundColor->r, backgroundColor->g, backgroundColor->b, 255);
	SDL_RenderClear(renderer);
	float opacity;
	switch (fadingState) {
	case FadingIn:
		opacity = fadeInTimer / fadeInDuration;
		//clamp the opacity between 1 and 0
		opacity = opacity < 0 ? 0 : opacity > 1 ? 1 : opacity;
		cout << "Rending at opacity: " << opacity << endl;
		SDL_SetTextureAlphaModFloat(logoTexture, opacity);
		SDL_RenderTexture(renderer, logoTexture, NULL, new SDL_FRect{148, 78, 32, 32});
		break;
	case Sustaining:
		opacity = 1;
		SDL_SetTextureAlphaModFloat(logoTexture, opacity);
		SDL_RenderTexture(renderer, logoTexture, NULL, new SDL_FRect{ 148, 78, 32, 32 });
		break;
	case FadingOut:
		opacity = fadeOutTimer / fadeOutDuration;
		//clamp the opacity between 1 and 0
		opacity = opacity < 0 ? 0 : opacity > 1 ? 1 : opacity;
		//flip the opacity (fade out not in)
		opacity = 1 - opacity;
		SDL_SetTextureAlphaModFloat(logoTexture, opacity);
		SDL_RenderTexture(renderer, logoTexture, NULL, new SDL_FRect{ 148, 78, 32, 32 });
		break;
	}
	SDL_RenderPresent(renderer);
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
