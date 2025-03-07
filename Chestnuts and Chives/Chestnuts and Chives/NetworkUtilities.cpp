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

void NetworkUtilities::SendMessageTo(string message, SDLNet_DatagramSocket* socket, SDLNet_Address* address, int port)
{
	//compresses string of binary into just a string
	string compressedMessage = PackMessage(message);
	//sends the compressed message to the specified port and address
	SDLNet_SendDatagram(socket, address, port, compressedMessage.c_str(), strlen(compressedMessage.c_str()));
}

NetworkMessageTypes NetworkUtilities::ProcessHeader(string inData)
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
	case 4: return Sync;
	case 5: return Test;
	default: return Error;
	}
	return Test;
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
string NetworkUtilities::AsBinaryString(int outBytes, int value)
{
	string digits = to_string(value);
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
	outString = outString.substr(0, outBytes * 8);
	return outString;
}
int NetworkUtilities::IntFromBinaryString(string binaryString, int digits)
{
	int out = 0;
	for (int i = 0; i < digits; i++) {
		int num = stoi(binaryString.substr(i * 4, 4),nullptr, 2);
		out += num * (i ^ 10);
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
NetworkMessage::NetworkMessage(SDLNet_Datagram* datagramToProcess)
{
	char* buffer = (char*)datagramToProcess->buf;
	string outData = NetworkUtilities::UnpackMessage(buffer);
	messageType = NetworkUtilities::ProcessHeader(outData);
	extraData = outData.substr(4);
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
bool NetworkUtilities::IsBinaryOnly(string message) {
	for (int i = 0; i < message.size(); i++) {
		if (!(message.at(i) == '0' || message.at(i) == '1')) {
			return false;
		}
	}
	return true;
}
