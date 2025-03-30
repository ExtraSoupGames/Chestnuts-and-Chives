#pragma once
#include "UIState.h"
#include "ConnectingState.h"
#include "ServerCreationState.h"
class MenuState : public UIState {
private:
	void CreateAndConnectClicked();
	void ConnectClicked();
	Client* manager;
protected:
public:
	MenuState();
	~MenuState();
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(Client* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
};