#pragma once
#include <string>
#include <SDL3_net/SDL_net.h>
#include <bitset>
#include <iostream>
using namespace std;
enum NetworkMessageTypes {
	Connect,
	ConnectConfirm,
	Heartbeat,
	Sync,
	Test,
	Error
};
static class NetworkUtilities {
private:
	static string PackMessage(string inData);
public:
	static void SendMessageTo(string message,SDLNet_DatagramSocket* socket, SDLNet_Address* address, int port);
	static bool IsBinaryOnly(string message);
	static NetworkMessageTypes ProcessHeader(string message);
	static string UnpackMessage(char* inData);

	static string AsBinaryString(int outBytes, int value);
	static int IntFromBinaryString(string binaryString, int digits);

	static string AsBinaryString(int outBytes, string value);
	static string StringFromBinaryString(string binaryString, int length);


};
class NetworkMessage {
private:
	NetworkMessageTypes messageType;
	string extraData;
public:
	NetworkMessage(SDLNet_Datagram* datagramToProcess);
	string Debug();
	NetworkMessageTypes GetMessageType();
	string GetExtraData();
};
