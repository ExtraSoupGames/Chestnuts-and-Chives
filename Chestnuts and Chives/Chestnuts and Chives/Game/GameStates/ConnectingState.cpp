#include "ConnectingState.h"
#include "ExtraSoupState.h"
void ConnectingState::Render(Renderer* renderer)
{
}

void ConnectingState::Update(int frameTime)
{
}

void ConnectingState::Initialize(Client* manager)
{
	manager->ConnectToServer("127.0.0.1");
	manager->SwitchState(new ExtraSoupState());
}

void ConnectingState::ManageInput(SDL_Event* e)
{
}

void ConnectingState::ProcessServerMessage(NetworkMessage* msg)
{
}
