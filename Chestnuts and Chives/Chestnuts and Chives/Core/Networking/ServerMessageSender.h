#pragma once
#include "MessageSender.h"
using namespace std;
struct ImportantBroadcast : public ImportantMessage {
	vector<ConnectedClient*> unconfirmedClients;
	void ConfirmationReceived(NetworkMessage* confirmationMessage);
	bool IsFullyConfirmed();
};
class ServerMessageSender : public MessageSender {
private:
	vector<ConnectedClient*> clients;
	vector<ImportantBroadcast*> broadcasts;
	void SendUnsentBroadcasts();
public:
	ServerMessageSender(SDLNet_DatagramSocket* socket, vector<ConnectedClient*> clients);
	void SendImportantMessage(NetworkMessageTypes type, string message, ConnectedClient* client);
	void BroadcastImportantMessage(NetworkMessageTypes type, string message);

	virtual void SendUnsentMessages() override;
	virtual void ConfirmationRecieved(NetworkMessage* message) override;

	void NewClientConnected(ConnectedClient* client);
	void ClientDisconnected(ConnectedClient* client);
};