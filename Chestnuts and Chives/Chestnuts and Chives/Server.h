#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
class Server
{
private:
	SDLNet_DatagramSocket* socket;
	SDLNet_Address* address;
	SDLNet_Address* clientAddress;
	void SendMessage();
public:
	Server();
	void Update();
	SDLNet_Address* GetAddress();
};

