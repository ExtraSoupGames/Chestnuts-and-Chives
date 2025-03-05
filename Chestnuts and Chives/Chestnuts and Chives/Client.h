#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include "Server.h"
class Client
{
private:
	SDLNet_DatagramSocket* socket;
	Server* connectedServer;
	void SendMessage();
public:
	Client(Server* s);
	void Update();
};

