#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include "NetworkUtilities.h"
#include "ConnectedClient.h"
using namespace std;
struct ImportantMessage {
	int ID;
	ConnectedClient* target;
	NetworkMessageTypes type;
	string message;
	ImportantMessage(string msg, ConnectedClient* msgTarget, int id, NetworkMessageTypes t) {
		message = NetworkUtilities::AsBinaryString(3, id) + msg;
		ID = id;
		target = msgTarget;
		type = t;
	}
	~ImportantMessage() {
		delete target;
	}
};
class MessageSender {
private:
protected:
	SDLNet_DatagramSocket* socket;
	vector<ImportantMessage*> messages;
	void IncrementNextMessage();
	int nextMessageID;
	MessageSender(SDLNet_DatagramSocket* socket);
	void SendImportantMessageTo(string message, NetworkMessageTypes type, SDLNet_Address* address, int port);
	void SendImportantMessageTo(string message, NetworkMessageTypes type, ConnectedClient* client);
public:
	virtual void SendUnsentMessages();
	virtual void ConfirmationRecieved(NetworkMessage* confirmationMessage);
	void SendImportantMessageConfirmation(NetworkMessage* importantMessage);
};