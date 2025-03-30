#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include "Server.h"
#include "AssetDictionary.h"
#include "ClientMessageSender.h"
#include "Renderer.h"
using namespace std;
class GameState;
class Client
{
private:
	//The client ID is 0 until the client connects to the server, at which point it is assigned a positive ID
	int clientID;
	int port;
	SDLNet_DatagramSocket* socket;
	SDLNet_Address* connectedServer;
	void ProcessIncoming();
	Server* gameServer;
	Renderer* renderer;
	ClientMessageSender* sender;
	bool connectAttempted = false;
	AssetDictionary<SDL_Texture*>* textureDict;
	GameState* state;
	int ticks;
public:
	Client(int portToUse, string windowName);
	void ConnectToServer(string serverAddress);
	void CreateServer(string serverAddress);
	void Update();
	bool IsConnected();
	void Render();
	void ManageInput(SDL_Event* e);
	void SendServerMessage(NetworkMessageTypes type, string msg);
	void SendImportantServerMessage(NetworkMessageTypes type, string message);
	bool SendImportantMessageConfirmation(NetworkMessage* msg);
	void SwitchState(GameState* newState);
	void TexturesLoaded(AssetDictionary<SDL_Texture*>* textures);
	SDL_Texture* GetTexture(string name);
};

