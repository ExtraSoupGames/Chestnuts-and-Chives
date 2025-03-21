#include "MessageSender.h"

void MessageSender::IncrementNextMessage()
{
	nextMessageID++;
	if (nextMessageID > 999) {
		nextMessageID = 0;
	}
}

MessageSender::MessageSender(SDLNet_DatagramSocket* pSocket)
{
	socket = pSocket;
	nextMessageID = 1;
}

void MessageSender::SendImportantMessageTo(string message, NetworkMessageTypes type, SDLNet_Address* address, int port)
{
	ImportantMessage* msg = new ImportantMessage(message, new ConnectedClient(address, port), nextMessageID, type);
	messages.push_back(msg);
	IncrementNextMessage();
}

void MessageSender::SendImportantMessageTo(string message, NetworkMessageTypes type, ConnectedClient* client)
{
	ImportantMessage* msg = new ImportantMessage(message, new ConnectedClient(*client), nextMessageID, type);
	messages.push_back(msg);
	IncrementNextMessage();

}

void MessageSender::SendUnsentMessages()
{
	for (ImportantMessage* message : messages) {
		NetworkUtilities::SendMessageTo(message->type, message->message, socket, message->target->address, message->target->clientPort);
	}
}

void MessageSender::ConfirmationRecieved(NetworkMessage* confirmationMessage)
{
	int messageID = NetworkUtilities::IntFromBinaryString(confirmationMessage->GetExtraData(), 3);
	messages.erase(remove_if(messages.begin(), messages.end(), [messageID](ImportantMessage* m) {return m->ID == messageID; }), messages.end());
}

void MessageSender::SendImportantMessageConfirmation(NetworkMessage* importantMessage)
{
	SDLNet_Address* address = importantMessage->GetAddress();;
	int port = importantMessage->GetPort();
	NetworkUtilities::SendMessageTo(ImportantMessageConfirmation, importantMessage->GetExtraData(), socket, address ,port);
}
