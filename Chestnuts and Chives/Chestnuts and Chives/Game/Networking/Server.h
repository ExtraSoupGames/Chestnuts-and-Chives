#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include <vector>
#include "NetworkUtilities.h"
#include "GameSave.h"
#include <fstream>
#include "ConnectedClient.h"
#include "ServerMessageSender.h"
using namespace std;
//forward declaration
class ServerState;
class Server
{
private:
	vector<ConnectedClient*>* connectedClients;
	SDLNet_DatagramSocket* socket;
	SDLNet_Address* address;
	ServerMessageSender* sender;
	int nextClientID;
	bool connectingAClient;
	SDLNet_Address* connectingClientsAddress;
	int connectingClientPort;
	void ProcessIncoming();

	int lastTicks;

	GameSave* save;
	ServerState* state;

	void ConfirmClientConnection(SDLNet_Address* clientAddress);
	void TryConnectClient(string inData, SDLNet_Address* clientAddress, int clientPort);
	bool IsAlreadyConnected(SDLNet_Address* address, int port);
public:
	Server(string addressIP);
	void Update();
	void Broadcast(string message);


	void SwitchState(ServerState* newState);
};