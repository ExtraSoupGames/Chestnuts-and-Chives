#include "AssetLoadingState.h"
#include "MenuState.h"
void AssetLoadingState::Exit()
{
	if (gameManager == nullptr) {
		throw new exception("Client is null");
	}
	gameManager->TexturesLoaded(loader->GetTextures());
	gameManager->SwitchState(new MenuState());
}

AssetLoadingState::AssetLoadingState()
{
	cout << "Constructor called" << endl;
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

void AssetLoadingState::Initialize(Client* manager)
{
	cout << "manager assigned" << endl;
	gameManager = manager;
}

void AssetLoadingState::ManageInput(SDL_Event* e)
{
}

void AssetLoadingState::ProcessServerMessage(NetworkMessage* msg)
{
}
