#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include <vector>
using namespace std;
struct ConnectedClient {
	string clientName;
	SDLNet_Address* address;
	int clientPort;
	ConnectedClient(SDLNet_Address* pAddress, string pClientName, int pClientPort);
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
	string connectingClientsName;
	int connectingClientPort;
	void SendMessageTo(SDLNet_Address* address, int clientPort, string message);
	void ProcessIncoming();
	bool IsAlreadyConnected(SDLNet_Address* address, int port, string clientName);
public:
	Server();
	void Update();
};