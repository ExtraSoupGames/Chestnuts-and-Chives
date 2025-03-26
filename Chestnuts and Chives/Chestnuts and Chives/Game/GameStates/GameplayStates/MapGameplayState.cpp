#include "MapGameplayState.h"
#include "Button.h"
void MapGameplayState::VoteButtonClicked()
{
	playerHasVoted = !playerHasVoted;
	gameManager->SendServerMessage(GameStateSync, playerHasVoted == true ? "1" : "0");
}

MapGameplayState::MapGameplayState()
{
	playerHasVoted = false;
}

MapGameplayState::~MapGameplayState()
{
	UIGameplayState::~UIGameplayState();
}

void MapGameplayState::Render(Renderer* renderer)
{
	renderer->FillBackground();
	UIGameplayState::Render(renderer);
	renderer->UpdateScreen();
}

void MapGameplayState::Update(int frameTime)
{
}

void MapGameplayState::Initialize(GameManager* manager)
{
	GameplayState::Initialize(manager);
	elements.push_back(new Button(10, 10, 48, 16, [this]() {VoteButtonClicked(); return true; }, gameManager));
}

void MapGameplayState::ManageInput(SDL_Event* e)
{
	UIGameplayState::ManageInput(e);
}

void MapGameplayState::ProcessServerMessage(NetworkMessage* msg)
{
}

string MapGameplayState::GetStateCode()
{
	return "0001";
}
