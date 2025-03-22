#include "ConnectingState.h"
#include "GameManager.h"
void ConnectingState::Render(Renderer* renderer)
{
}

void ConnectingState::Update(int frameTime)
{
}

void ConnectingState::Initialize(GameManager* manager)
{
	manager->ConnectToServer();
	manager->SwitchState(new ExtraSoupState());
}

void ConnectingState::ManageInput(SDL_Event* e)
{
}
