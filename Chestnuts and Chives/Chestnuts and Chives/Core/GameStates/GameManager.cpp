#include "GameManager.h"
#include "Client.h"
#include "ConnectedState.h"
GameManager::GameManager(Renderer* renderer, Client* owner)
{
	this->renderer = renderer;
	initialized = false;
	ticks = 0;
	gameState = nullptr;
	client = owner;
	textures = nullptr;
}

void GameManager::SwitchState(GameState* state)
{
	if (gameState != nullptr) {
		delete gameState;
	}
	gameState = state;
	state->Initialize(this);
}

SDL_Texture* GameManager::GetTexture(string textureName)
{
	SDL_Texture* texture = textures->GetItem(textureName);
	if (texture == nullptr) {
		cout << "Returned null texture, texture with name: " << textureName << " wasnt loaded correctly" << endl;
	}
	return textures->GetItem(textureName);
}

void GameManager::Render()
{
	if (!initialized) {
		return;
	}
	gameState->Render(renderer);
}

void GameManager::Update()
{
	if (!initialized) {
		return;
	}
	int frameTimeMillis = SDL_GetTicks() - ticks;
	ticks = SDL_GetTicks();
	gameState->Update(frameTimeMillis);
}

void GameManager::Initialize()
{
	if (initialized) {
		cout << "Game Manager initialize requested, but manager is already initialized" << endl;
		return;
	}
	initialized = true;
	SwitchState(new AssetLoadingState());
	cout << "GameManager initialized" << endl;
	ticks = SDL_GetTicks();
}

void GameManager::ManageInput(SDL_Event* e)
{
	if (!initialized) {
		return;
	}
	gameState->ManageInput(e);
}

void GameManager::TexturesLoaded(std::unique_ptr<AssetDictionary<SDL_Texture*>> textureDict) {
	textures = std::move(textureDict);  // Transfers ownership
}

void GameManager::ConnectToServer()
{
	client->ConnectToServer("127.0.0.1");
}

void GameManager::CreateServer()
{
	client->CreateServer("127.0.0.1");
}

void GameManager::ProcessServerMessage(NetworkMessage* msg)
{
	if (msg->GetMessageType() == GameStateSync) {
		if (dynamic_cast<ConnectedState*>(gameState) == nullptr) {
			SwitchState(new ConnectedState());
		}
	}
	gameState->ProcessServerMessage(msg);
}

void GameManager::SendServerMessage(NetworkMessageTypes type, string msg)
{
	client->SendServerMessage(type, msg);
}
