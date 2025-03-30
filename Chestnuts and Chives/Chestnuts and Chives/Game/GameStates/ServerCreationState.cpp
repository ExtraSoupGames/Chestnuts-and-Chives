#include "ServerCreationState.h"

void ServerCreationState::Render(Renderer* renderer)
{
}

void ServerCreationState::Update(int frameTime)
{
}

void ServerCreationState::Initialize(Client* manager)
{
	manager->CreateServer("127.0.0.1");
	manager->SwitchState(new ConnectingState());
}

void ServerCreationState::ManageInput(SDL_Event* e)
{
}

void ServerCreationState::ProcessServerMessage(NetworkMessage* msg)
{
}
