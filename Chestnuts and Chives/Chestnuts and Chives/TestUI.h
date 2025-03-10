#pragma once
#include "UIState.h"
#include "Renderer.h"
class TestUI : public UIState
{
private:
public:
	TestUI();
	~TestUI();

	virtual void Update(int frameTime) override;
	virtual void Render(Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
};

