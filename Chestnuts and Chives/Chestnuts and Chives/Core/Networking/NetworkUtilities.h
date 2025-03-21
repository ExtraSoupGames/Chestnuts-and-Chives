#pragma once
#include <string>
#include <SDL3_net/SDL_net.h>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;
enum NetworkMessageTypes {
	Connect,
	ConnectConfirm,
	Heartbeat,
	GameStateChange,
	Test,
	ImportantMessageConfirmation,
	Error
};
class NetworkMessage {
private:
	NetworkMessageTypes messageType;
	SDLNet_Address* fromAddress;
	int fromPort;
	string extraData;
public:
	NetworkMessage();
	NetworkMessage(SDLNet_Datagram* datagramToProcess);
	string Debug();
	NetworkMessageTypes GetMessageType();
	string GetExtraData();
	SDLNet_Address* GetAddress();
	int GetPort();
};

static class NetworkUtilities {
private:
	static vector<Uint8>* PackMessage(string inData);

public:
	/*Gets the next incoming message on the socket...
Implementation should look something like this:
NetworkMessage* message = nullptr;
while(GetNextIncoming(socket, message){
	//process data and message here
	delete message;
}*/
	static bool GetNextIncoming(SDLNet_DatagramSocket* socket, NetworkMessage* &message);

	static void SendMessageTo(NetworkMessageTypes messageType, string message,SDLNet_DatagramSocket* socket, SDLNet_Address* address, int port);
	static bool IsBinaryOnly(string message);
	static string UnpackMessage(Uint8* inData, int messageLength);

	static NetworkMessageTypes UnpackHeader(string message);
	static string PackHeader(NetworkMessageTypes type);


	//converts a decimal integer into a binary coded decimal string
	static string AsBinaryString(int outNibbles, int value);
	static int IntFromBinaryString(string binaryString, int digits);

	static string AsBinaryString(int outBytes, string value);
	static string StringFromBinaryString(string binaryString, int length);
};