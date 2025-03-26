#include "AssetLoadingState.h"
#include "MenuState.h"
void AssetLoadingState::Exit()
{
	gameManager->TexturesLoaded(loader->GetTextures());
	gameManager->SwitchState(new MenuState());
}

AssetLoadingState::AssetLoadingState()
{
	gameManager = nullptr;
	loader = new AssetLoader();
}

AssetLoadingState::~AssetLoadingState()
{
	delete loader;
}

void AssetLoadingState::Update(int frameTime)
{
}

void AssetLoadingState::Render(Renderer* renderer)
{
	float percentComplete = (loader->LoadNextTexture(renderer) * 100);
	if (percentComplete == -100) {
		Exit();
		return;
	}
	cout << "Percent of textures loaded: " << percentComplete << "%" << endl;;
}

void AssetLoadingState::Initialize(GameManager* manager)
{
	gameManager = manager;
}

void AssetLoadingState::ManageInput(SDL_Event* e)
{
}

void AssetLoadingState::ProcessServerMessage(NetworkMessage* msg)
{
}
