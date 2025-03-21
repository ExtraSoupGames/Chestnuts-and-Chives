#include "ServerMessageSender.h"
void ServerMessageSender::BroadcastImportantMessage(NetworkMessageTypes type, string message) {
}
void ServerMessageSender::SendImportantMessage(NetworkMessageTypes type, string message, ConnectedClient* client)
{
	MessageSender::SendImportantMessageTo(message, type, client);
}
ServerMessageSender::ServerMessageSender(SDLNet_DatagramSocket* socket, vector<ConnectedClient*> connectedClients) : MessageSender(socket)
{
	clients = vector<ConnectedClient*>(connectedClients);
}
void ServerMessageSender::ConfirmationRecieved(NetworkMessage* message)
{
	int messageID = NetworkUtilities::IntFromBinaryString(message->GetExtraData(), 3);
	messages.erase(remove_if(messages.begin(), messages.end(), [messageID](ImportantMessage* m) {return m->ID == messageID; }), messages.end());
	auto broadcast = find_if(broadcasts.begin(), broadcasts.end(), [messageID](ImportantBroadcast* b) {return b->ID == messageID; });
	if (broadcast != broadcasts.end()) {
		(*broadcast)->ConfirmationReceived(message);
		if ((*broadcast)->IsFullyConfirmed()) {
			broadcasts.erase(remove(broadcasts.begin(), broadcasts.end(), *broadcast), broadcasts.end());
		}
	}
	//TODO redo this so that commonalities are reused but the broadcasts are also processed
}

void ServerMessageSender::NewClientConnected(ConnectedClient* client)
{
	clients.push_back(new ConnectedClient(*client));
}

void ServerMessageSender::ClientDisconnected(ConnectedClient* client)
{
	clients.erase(remove_if(clients.begin(), clients.end(),
			[client](ConnectedClient* disconnector) {return (SDLNet_GetAddressString(disconnector->address) == SDLNet_GetAddressString(client->address) && disconnector->clientPort == client->clientPort); }),
		clients.end());
}

void ServerMessageSender::SendUnsentMessages()
{
	SendUnsentBroadcasts();
	MessageSender::SendUnsentMessages();
}
void ServerMessageSender::SendUnsentBroadcasts()
{
	//TODO iterate through broadcasts and send ONLY TO CLIENTS THAT HAVENT RECEIVED YET
}

void ImportantBroadcast::ConfirmationReceived(NetworkMessage* confirmationMessage)
{
	auto client = find_if(unconfirmedClients.begin(),
		unconfirmedClients.end(),
		[confirmationMessage](ConnectedClient* c) {return (c->address == confirmationMessage->GetAddress() && c->clientPort == confirmationMessage->GetPort()); });
	if (client == unconfirmedClients.end()) {
		return;
	}
	unconfirmedClients.erase(remove(unconfirmedClients.begin(), unconfirmedClients.end(), *client), unconfirmedClients.end());
}

bool ImportantBroadcast::IsFullyConfirmed()
{
	return unconfirmedClients.empty();
}
