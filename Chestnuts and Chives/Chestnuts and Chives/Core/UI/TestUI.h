#pragma once
#include "UIState.h"
#include "Map.h"
#include "Renderer.h"
class TestUI : public UIState
{
private:
	Map* map;
public:
	TestUI();
	~TestUI();

	virtual void Update(int frameTime) override;
	virtual void Render(Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
};

