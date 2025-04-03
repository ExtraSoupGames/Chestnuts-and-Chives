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
	gameManager = manager;
	TTF_Font* font = TTF_OpenFont("Assets/Fonts/ChestnutsAndChives.ttf", 15);
	if (!font) {
		cout << "Font not loaded properly" << SDL_GetError() <<endl;
	}
	gameManager->FontLoaded(font);
}

void AssetLoadingState::ManageInput(SDL_Event* e)
{
}

void AssetLoadingState::ProcessServerMessage(NetworkMessage* msg)
{
}
