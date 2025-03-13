#include "TestUI.h"

TestUI::TestUI()
{
	map = nullptr;
}

TestUI::~TestUI()
{
}

void TestUI::Update(int frameTime)
{
}

void TestUI::Render(Renderer* renderer)
{
	renderer->FillBackground();
	map->Render(renderer);
	renderer->UpdateScreen();
}

void TestUI::Initialize(GameManager* manager)
{
	map = new Map(0, 20, manager);
}

void TestUI::ManageInput(SDL_Event* e) {
	//TODO change this to mouse controls and or cross platform controls and or make a whole input processing class that allows for custom input maps and various controllers
	//Note to self probably best to do this earlier before any gameplay implementation as making a new system takes a set amount of time but migrating to it could take ages if i do it too late
	if (e->type == SDL_EVENT_KEY_DOWN) {
		if (e->key.key == SDLK_A) {
			map->UpdateOffset(-5, 0);
		}
		if (e->key.key == SDLK_D) {
			map->UpdateOffset(5, 0);
		}
		if (e->key.key == SDLK_W) {
			map->UpdateOffset(0, -5);
		}
		if (e->key.key == SDLK_S) {
			map->UpdateOffset(0, 5);
		}
	}
}