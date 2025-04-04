#include "TestGameplayState.h"

TestGameplayState::TestGameplayState()
{
	playerHasVoted = false;
	testText = nullptr;
}

void TestGameplayState::Render(Renderer* renderer)
{
	renderer->FillBackground(playerHasVoted ? new SDL_Color{ 10, 10, 10 } : new SDL_Color{ 100, 100, 100 });
	testText->Render(renderer);
	renderer->UpdateScreen();
}

void TestGameplayState::Update(int frameTime)
{
}

void TestGameplayState::Initialize(Client* manager)
{
	GameplayState::Initialize(manager);
	string text = "HELLO";
	testText = new Text(100, 100, text, gameManager, 100, 100);
}

void TestGameplayState::ManageInput(SDL_Event* e)
{
	UIGameplayState::ManageInput(e);
	if (e->type == SDL_EVENT_KEY_DOWN) {
		if (e->key.key == SDLK_A) {
			playerHasVoted = !playerHasVoted;
			gameManager->SendImportantServerMessage(GameStateSync, playerHasVoted == true ? "1" : "0");
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
