#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include <vector>
#include "NetworkUtilities.h"
using namespace std;
struct ConnectedClient {
	SDLNet_Address* address;
	int clientPort;
	ConnectedClient(SDLNet_Address* pAddress, int pClientPort);
};
class Server
{
private:
	vector<ConnectedClient*>* connectedClients;
	SDLNet_DatagramSocket* socket;
	SDLNet_Address* address;
	int nextClientID;
	bool connectingAClient;
	SDLNet_Address* connectingClientsAddress;
	int connectingClientPort;
	void ProcessIncoming();
	void Broadcast(string message);

	void UpdateState();
	void ConfirmClientConnection(SDLNet_Address* clientAddress);
	void TryConnectClient(string inData, SDLNet_Address* clientAddress, int clientPort);
	bool IsAlreadyConnected(SDLNet_Address* address, int port);
public:
	Server(string addressIP);
	void Update();
};