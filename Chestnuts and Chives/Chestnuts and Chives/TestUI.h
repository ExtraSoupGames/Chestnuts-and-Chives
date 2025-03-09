#pragma once
#include "UIState.h"
class TestUI : public UIState
{
private:
public:
	TestUI();
	~TestUI();

	virtual void Update(float frameTime) override;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Exit() override;
};

