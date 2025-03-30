#include "MenuState.h"
#include "Button.h"
void MenuState::CreateAndConnectClicked()
{
	manager->SwitchState(new ServerCreationState());
}
void MenuState::ConnectClicked()
{
	manager->SwitchState(new ConnectingState());
}
MenuState::MenuState()
{
	manager = nullptr;
}
MenuState::~MenuState() {
	UIState::~UIState();
}

void MenuState::Render(Renderer* renderer)
{
	//Do rendering here
	renderer->FillBackground();
	UIState::Render(renderer);
	renderer->UpdateScreen();
}

void MenuState::Update(int frameTime)
{
}

void MenuState::Initialize(Client* gameManager)
{
	manager = gameManager;
	elements.push_back(new Button(10, 10, 48, 16, [this]() {CreateAndConnectClicked(); return true; }, manager));
	elements.push_back(new Button(10, 40, 64, 16, [this]() {CreateAndConnectClicked(); return true; }, manager));
	elements.push_back(new Button(10, 80, 128, 16, [this]() {ConnectClicked(); return true; }, manager));
}

void MenuState::ManageInput(SDL_Event* e)
{
	UIState::ManageInput(e);
}

void MenuState::ProcessServerMessage(NetworkMessage* msg)
{
}
