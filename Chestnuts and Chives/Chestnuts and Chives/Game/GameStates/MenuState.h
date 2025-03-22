#pragma once
#include "UIState.h"
#include "SDL3/SDL.h"
#include "Button.h"
class MenuState : public UIState {
private:
	void CreateAndConnectClicked();
	void ConnectClicked();
	GameManager* manager;
protected:
public:
	MenuState();
	~MenuState();
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;

};