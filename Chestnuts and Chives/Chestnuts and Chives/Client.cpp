#include "Client.h"
Client::Client(int portToUse) {
    clientID = 0;
    port = portToUse;
    socket = nullptr;
    connectedServer = nullptr;
}
void Client::ConnectToServer(string serverAddress)
{
    connectedServer = SDLNet_ResolveHostname(serverAddress.c_str());
    SDLNet_WaitUntilResolved(connectedServer, 1000);
    socket = SDLNet_CreateDatagramSocket(connectedServer, port);
}
void Client::ProcessIncoming() {
    SDLNet_Datagram* incoming;
    while (SDLNet_ReceiveDatagram(socket, &incoming)) {
        if (incoming) {
            NetworkMessage* msg = new NetworkMessage(incoming);
            if (msg->GetMessageType() == Connect) {
                clientID = NetworkUtilities::IntFromBinaryString(msg->GetExtraData(), 1);
                string message = "0010";
                NetworkUtilities::SendMessageTo(message, socket, connectedServer, 66661);
            }
            SDLNet_DestroyDatagram(incoming);
        }
        else {
            break;
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
        string message = "0001";
        NetworkUtilities::SendMessageTo(message, socket, connectedServer, 66661);
        return;
    }
    string message = "0011" + NetworkUtilities::AsBinaryString(1, clientID);
    NetworkUtilities::SendMessageTo(message, socket, connectedServer, 66661);
}

bool Client::IsConnected()
{
    return connectedServer != nullptr;
}
