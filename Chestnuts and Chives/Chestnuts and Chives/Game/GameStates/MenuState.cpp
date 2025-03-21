#include "MenuState.h"
bool test() {
	return false;
}
MenuState::MenuState()
{
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

void MenuState::Initialize(GameManager* manager)
{
elements.push_back(new Button(10, 10, 50, 50, test, manager));
}

void MenuState::ManageInput(SDL_Event* e)
{
}
