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
    SDLNet_Datagram* incoming;
    while (SDLNet_ReceiveDatagram(socket, &incoming)) {
        if (incoming) {
            string inData = string((char*)incoming->buf);
            SDLNet_Address* clientAddress = SDLNet_RefAddress(incoming->addr);
            int clientPort = incoming->port;
            NetworkMessage* msg = new NetworkMessage(incoming);

            switch(msg->GetMessageType()){
            case Connect:
                TryConnectClient(inData, clientAddress, clientPort);
                break;
            case ConnectConfirm:
                ConfirmClientConnection(clientAddress);
                break;
            case Heartbeat:
                break;
            }
            SDLNet_DestroyDatagram(incoming);
        }
        else {
            break;
        }
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
            string message = "0001" + NetworkUtilities::AsBinaryString(1, nextClientID);
            NetworkUtilities::SendMessageTo(message, socket, clientAddress, clientPort);
        }
        else if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
            if (clientPort == connectingClientPort) {
                string message = "0001" + NetworkUtilities::AsBinaryString(1, nextClientID);
                NetworkUtilities::SendMessageTo(message, socket, clientAddress, clientPort);
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
