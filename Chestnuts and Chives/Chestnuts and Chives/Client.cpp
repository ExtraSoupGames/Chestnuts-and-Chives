#include "Client.h"
void Client::SendMessage(string message)
{
    SDLNet_SendDatagram(socket, connectedServer, 66661, message.c_str(), strlen(message.c_str()));
}
Client::Client(string clientName, int portToUse) {
    clientID = 0;
    port = portToUse;
    socket = nullptr;
    connectedServer = nullptr;
    this->clientName = clientName;
}
void Client::ConnectToServer(string serverAddress)
{
    connectedServer = SDLNet_ResolveHostname(serverAddress.c_str());
    SDLNet_WaitUntilResolved(connectedServer, 1000);
    socket = SDLNet_CreateDatagramSocket(connectedServer, port);
}
void Client::ProcessIncoming() {
    SDLNet_Datagram* incoming;
    if (SDLNet_ReceiveDatagram(socket, &incoming)) {
        if (incoming) {
            string inData = string((char*)incoming->buf);
            if (inData.substr(0, 4) == "0000") {
                clientID = stoi(inData.substr(4,1));
                string message = "0001" + clientName;
                SendMessage(message);
            }
            SDLNet_DestroyDatagram(incoming);
        }
    }
}
void Client::Update() {
    if (connectedServer == nullptr) {
        return;
    }
    ProcessIncoming();
    if (clientID == 0) {
        //if the client ID is 0 then this client has not yet connected to the server
        string message = "0000" + clientName;
        SendMessage(message);
        return;
    }
    string message = "0002" + to_string(clientID);
    SendMessage(message);
}

bool Client::IsConnected()
{
    return connectedServer != nullptr;
}
