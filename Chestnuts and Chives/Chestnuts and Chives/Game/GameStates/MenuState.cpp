#include "MenuState.h"
bool test() {
	cout << "Button pressed to" << endl;
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
	elements.push_back(new Button(10, 10, 48, 16, test, manager));
	elements.push_back(new Button(10, 40, 64, 16, test, manager));
	elements.push_back(new Button(10, 80, 128, 16, test, manager));
}

void MenuState::ManageInput(SDL_Event* e)
{
	UIState::ManageInput(e);
}
