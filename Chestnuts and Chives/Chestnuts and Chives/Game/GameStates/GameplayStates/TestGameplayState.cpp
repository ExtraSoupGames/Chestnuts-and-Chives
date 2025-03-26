#include "TestGameplayState.h"

TestGameplayState::TestGameplayState()
{
	playerHasVoted = false;
}

void TestGameplayState::Render(Renderer* renderer)
{
	renderer->FillBackground(new SDL_Color{5, 5, 5, 5});
	renderer->UpdateScreen();
}

void TestGameplayState::Update(int frameTime)
{
}

void TestGameplayState::Initialize(GameManager* manager)
{
	GameplayState::Initialize(manager);
}

void TestGameplayState::ManageInput(SDL_Event* e)
{
	UIGameplayState::ManageInput(e);
	if (e->type == SDL_EVENT_KEY_DOWN) {
		if (e->key.key == SDLK_A) {
			playerHasVoted = !playerHasVoted;
			gameManager->SendServerMessage(GameStateSync, playerHasVoted == true ? "1" : "0");
		}
	}
}

void TestGameplayState::ProcessServerMessage(NetworkMessage* msg)
{
}

string TestGameplayState::GetStateCode()
{
	return "0000";
}
