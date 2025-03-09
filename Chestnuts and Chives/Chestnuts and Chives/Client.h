#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include "Server.h"
#include "ExtraSoupState.h"
using namespace std;
class Client
{
private:
	//The client ID is 0 until the client connects to the server, at which point it is assigned a positive ID
	int clientID;
	int port;
	SDLNet_DatagramSocket* socket;
	SDLNet_Address* connectedServer;
	void ProcessIncoming();
	GameManager* gameManager;
public:
	Client(int portToUse, GameManager* gameManager);
	void ConnectToServer(string serverAddress);
	void Update();
	bool IsConnected();
	void Render(SDL_Renderer* renderer);
};

