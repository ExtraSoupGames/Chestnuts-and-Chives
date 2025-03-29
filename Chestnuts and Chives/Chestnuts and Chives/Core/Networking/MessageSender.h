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
	int updatesUntilResendMessages;
	int resendMessageRate;
protected:
	SDLNet_DatagramSocket* socket;
	vector<ImportantMessage*> messages;
	vector<int> receivedMessages;
	void IncrementNextMessage();
	int nextMessageID;
	MessageSender(SDLNet_DatagramSocket* socket);
	void SendImportantMessageTo(string message, NetworkMessageTypes type, SDLNet_Address* address, int port);
	void SendImportantMessageTo(string message, NetworkMessageTypes type, ConnectedClient* client);
	bool ShouldResendMessages();
public:
	virtual void SendUnsentMessages(bool skipCheck);

	virtual void ConfirmationRecieved(NetworkMessage* confirmationMessage);
	//returns true if this is the first time the message has been received
	//Note that the confirmation message is sent regardless of wether or not it is the first time since the confirmation may not be received
	virtual bool SendImportantMessageConfirmation(NetworkMessage* importantMessage);
};