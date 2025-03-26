#pragma once
#include "UIGameplayState.h"
#include "SDL3/SDL.h"
class MapGameplayState : public UIGameplayState {
private:
	void VoteButtonClicked();
	bool playerHasVoted;
protected:
public:
	MapGameplayState();
	~MapGameplayState() override;
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
	virtual string GetStateCode() override;
};