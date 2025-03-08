#include "Server.h"
Server::Server() {
    address = SDLNet_ResolveHostname("127.0.0.1");
    if (address == nullptr) {
        std::cout << ("Address is invalid!") << std::endl;
    }
    //block until the address gets resolved, wait indefinitely
    SDLNet_WaitUntilResolved(address, -1);
    socket = SDLNet_CreateDatagramSocket(address, 66661);
    if (!socket) {
        printf("Failed to create UDP socket: %s\n", SDL_GetError());
    }
    nextClientID = 1;
    connectingAClient = false;
    connectingClientsAddress = nullptr;
    connectedClients = new vector<ConnectedClient*>();
    connectingClientPort = 0;
}
bool Server::IsAlreadyConnected(SDLNet_Address* address, int port) {
    for (int i = 0; i < connectedClients->size(); i++) {
        if (SDLNet_GetAddressString(address) == SDLNet_GetAddressString(connectedClients->at(i)->address)) {
            if (port == connectedClients->at(i)->clientPort) {
                cout << "A client tried to connect but they were already connected!" << endl;
                return true;
            }
        }
    }
    return false;
}

void Server::ProcessIncoming() {
    NetworkMessage* message = nullptr;
    while(NetworkUtilities::GetNextIncoming(socket, message)){
        switch(message->GetMessageType()){
        case Connect:
            TryConnectClient(message->GetExtraData(), message->GetAddress(), message->GetPort());
            break;
        case ConnectConfirm:
            ConfirmClientConnection(message->GetAddress());
            break;
        case Heartbeat:
            break;
        }
        delete message;
    }
}
void Server::ConfirmClientConnection(SDLNet_Address* clientAddress)
{
    if (!connectingAClient) {
        return;
    }
    if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
        connectingAClient = false;
        nextClientID++;
        connectedClients->push_back(new ConnectedClient(connectingClientsAddress, connectingClientPort));
        connectingClientsAddress = nullptr;
        cout << "Successfully connected client with ID: " << (nextClientID - 1) << endl;
    }
}
void Server::TryConnectClient(string inData, SDLNet_Address* clientAddress, int clientPort)
{
    if (!IsAlreadyConnected(clientAddress, clientPort)) {
        if (!connectingAClient) {
            connectingAClient = true;
            connectingClientsAddress = clientAddress;
            connectingClientPort = clientPort;
            string message = NetworkUtilities::AsBinaryString(1, nextClientID);
            NetworkUtilities::SendMessageTo(Connect, message, socket, clientAddress, clientPort);
        }
        else if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
            if (clientPort == connectingClientPort) {
                string message = NetworkUtilities::AsBinaryString(1, nextClientID);
                NetworkUtilities::SendMessageTo(Connect, message, socket, clientAddress, clientPort);
            }
        }
    }
}
void Server::Update() {
    ProcessIncoming();
}

ConnectedClient::ConnectedClient(SDLNet_Address* pAddress, int pClientPort)
{
    address = pAddress;
    clientPort = pClientPort;
}
