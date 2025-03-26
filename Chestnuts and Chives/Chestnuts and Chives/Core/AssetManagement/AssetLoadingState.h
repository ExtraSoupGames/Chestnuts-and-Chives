#pragma once
#include "ExtraSoupState.h"
#include "GameState.h"
#include "AssetLoader.h"
class AssetLoadingState : public GameState
{
private:
	AssetLoader* loader;
	void Exit();
	GameManager* gameManager;
public:
	AssetLoadingState();
	~AssetLoadingState() override;


	virtual void Update(int frameTime) override;
	virtual void Render(Renderer* renderer) override;
	virtual void Initialize(GameManager* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
};

