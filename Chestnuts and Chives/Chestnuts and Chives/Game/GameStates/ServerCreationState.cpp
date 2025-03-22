#include "ServerCreationState.h"

#include "GameManager.h"
void ServerCreationState::Render(Renderer* renderer)
{
}

void ServerCreationState::Update(int frameTime)
{
}

void ServerCreationState::Initialize(GameManager* manager)
{
	manager->CreateServer();
	manager->SwitchState(new ConnectingState());
}

void ServerCreationState::ManageInput(SDL_Event* e)
{
}
