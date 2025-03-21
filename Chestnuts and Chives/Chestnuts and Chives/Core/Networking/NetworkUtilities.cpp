#include "NetworkUtilities.h"

string NetworkUtilities::PackMessage(string inData)
{
	//ensure message is only 1s and 0s
	if (!IsBinaryOnly(inData)) {
		cout << "Error while sending message, message was not exclusively binary characters. problem message: " << inData << endl;
		return inData;
	}
	//pad message to a byte
	while (inData.size() % 8 != 0) {
		inData.append("0");
	}
	//process message into compressed form
	string compressedMessage = "";
	//iterates through the message, 1 byte at a time
	for (int i = 0; i < inData.size() / 8; i++) {
		//processes the byte into its compressed form
		char newBits = stoi(inData.substr(i * 8, 8), nullptr, 2);
		//append the new byte to the compressed message
		compressedMessage += (newBits);
	}
	return compressedMessage;
}
bool NetworkUtilities::GetNextIncoming(SDLNet_DatagramSocket* socket, NetworkMessage* &message)
{
	SDLNet_Datagram* incoming;
	if (SDLNet_ReceiveDatagram(socket, &incoming)) {
		if (!incoming) {
			return false;
		}
		message = (new NetworkMessage(incoming));
		SDLNet_DestroyDatagram(incoming);
		return message != nullptr;
	}
	return false;
}

void NetworkUtilities::SendMessageTo(NetworkMessageTypes messageType, string message, SDLNet_DatagramSocket* socket, SDLNet_Address* address, int port)
{
	//the header of the message as 4 bits in a string
	string messageHeader = AsBinaryString(1, messageType + 1);
	//compresses string of binary into just a string
	string compressedMessage = PackMessage(messageHeader + message);
	//sends the compressed message to the specified port and address
	SDLNet_SendDatagram(socket, address, port, compressedMessage.c_str(), strlen(compressedMessage.c_str()));
}

NetworkMessageTypes NetworkUtilities::UnpackHeader(string inData)
{
	int length = inData.size();
	if (length < 4) {
		return Error;
	}
	int header = stoi(inData.substr(0, 4), nullptr, 2);
	switch (header) {
	case 1: return Connect;
	case 2: return ConnectConfirm;
	case 3: return Heartbeat;
	case 4: return GameStateChange;
	case 5: return Test;
	case 6: return ImportantMessageConfirmation;
	default: return Error;
	}
	return Test;
}
string NetworkUtilities::PackHeader(NetworkMessageTypes type) {
	switch (type) {
	case Connect: return AsBinaryString(1, 1);
	case ConnectConfirm: return AsBinaryString(1, 2);
	case Heartbeat: return AsBinaryString(1, 3);
	case GameStateChange: return AsBinaryString(1, 4);
	case Test: return AsBinaryString(1, 5);
	case ImportantMessageConfirmation: return AsBinaryString(1, 6);
	}
}

string NetworkUtilities::UnpackMessage(char* inData)
{
	string unpackedMessage = "";
	//convert to a string for easier manipulation
	string inMessage = string(inData);
	//iterate through the message to unpack each byte
	for (int i = 0; i < inMessage.size(); i++) {
		//convert each char into a bitset of 8 bits
		bitset<8> newBits = inMessage.at(i);
		//add the bits to the unpacked message
		unpackedMessage += newBits.to_string();
	}
	if (!IsBinaryOnly(unpackedMessage)) {
		cout << "Error while unpacking message, not all returned characters were 1s and 0s. Problem message: " << unpackedMessage << endl;
	}
	return unpackedMessage;

}
//returns the int in BCD(Binary coded decimal) form
string NetworkUtilities::AsBinaryString(int outNibbles, int value)
{
	string digits = to_string(value);
	while (digits.size() < outNibbles) {
		digits = "0" + digits;
	}
	string outString = "";
	for (int i = 0; i < digits.size(); i++) {
		bitset<4> newBits = stoi(digits.substr(i, 1));
		string newNibble = newBits.to_string();
		if (!IsBinaryOnly(newNibble) || !newNibble.size() == 4) {
			cout << "Error processing integer into binary coded decimal. Problem bits: " << newNibble << endl;
			continue;
		}
		outString += (newNibble);
	}
	cout << "Turned digits: " << digits << " into " << outString << endl;
	outString = outString.substr(0, outNibbles * 4);
	return outString;
}
int NetworkUtilities::IntFromBinaryString(string binaryString, int digits)
{
	int out = 0;
	for (int i = 0; i < digits; i++) {
		int num = stoi(binaryString.substr(i * 4, 4),nullptr, 2);
		out = (out * 10) + num;
	}
	return out;
}
string NetworkUtilities::AsBinaryString(int outBits, string value) {
	string outString = "";
	for (int i = 0; i < value.size(); i++) {
		outString.push_back(stoi(value.substr(i, 1), nullptr, 2));
	}
	return outString;
}
NetworkMessage::NetworkMessage()
{
}
NetworkMessage::NetworkMessage(SDLNet_Datagram* datagramToProcess)
{
	char* buffer = (char*)datagramToProcess->buf;
	string outData = NetworkUtilities::UnpackMessage(buffer);
	messageType = NetworkUtilities::UnpackHeader(outData);
	extraData = outData.substr(4);
	fromAddress = SDLNet_RefAddress(datagramToProcess->addr);
	fromPort = datagramToProcess->port;
}

string NetworkMessage::Debug()
{
	return "The type of this message is: " + to_string(messageType) + " And the contents are: " + extraData;
}
NetworkMessageTypes NetworkMessage::GetMessageType() {
	return messageType;
}
string NetworkMessage::GetExtraData()
{
	return extraData;
}
SDLNet_Address* NetworkMessage::GetAddress()
{
	return fromAddress;
}
int NetworkMessage::GetPort()
{
	return fromPort;
}
bool NetworkUtilities::IsBinaryOnly(string message) {
	for (int i = 0; i < message.size(); i++) {
		if (!(message.at(i) == '0' || message.at(i) == '1')) {
			return false;
		}
	}
	return true;
}
