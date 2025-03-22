#pragma once
#include "GameState.h"
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ExtraSoupState.h"
#include <string>
#include "Renderer.h"
#include "AssetDictionary.h"
#include "AssetLoadingState.h"
using namespace std;
class Client;
class GameManager
{
private:
	GameState* gameState;
	Renderer* renderer;
	int ticks;
	bool initialized;
	AssetDictionary<SDL_Texture*> textures;
	Client* client;
public:
	GameManager(Renderer* renderer, Client* client);
	//Switch to a new state - to use this pass in a newly allocated GameState and it will automatically be deleted when a new state is switched to
	void SwitchState(GameState* state);
	SDL_Texture* GetTexture(string textureName);
	void Render();
	void Update();
	//This should only be called once and will put the game into an ExtraSoupState
	void Initialize();
	//pass the input down to the current state
	void ManageInput(SDL_Event* e);
	//called once game has been loaded to store textures here so all gamestates can access them
	void TexturesLoaded(AssetDictionary<SDL_Texture*>* textureDict);
	//used by states to connect the client to a server
	void ConnectToServer();
	//used by states to use the client to create a server
	void CreateServer();
};

