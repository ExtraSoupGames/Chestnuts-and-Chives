#include "Server.h"
void Server::SendMessageTo(SDLNet_Address* recipientAddress, int clientPort, string message)
{
    SDLNet_SendDatagram(socket, recipientAddress, clientPort, message.c_str(), strlen(message.c_str()));
}
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
bool Server::IsAlreadyConnected(SDLNet_Address* address, int port, string clientName) {
    for (int i = 0; i < connectedClients->size(); i++) {
        if (SDLNet_GetAddressString(address) == SDLNet_GetAddressString(connectedClients->at(i)->address)) {
            if (clientName == connectedClients->at(i)->clientName) {
                if (port == connectedClients->at(i)->clientPort) {
                    cout << "A client tried to connect but they were already connected!" << endl;
                    return true;
                }
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
            if (inData.substr(0, 4) == "0000") {
                string clientName = inData.substr(4);
                if (!IsAlreadyConnected(clientAddress, clientPort, clientName)) {
                    if (!connectingAClient) {
                        connectingAClient = true;
                        connectingClientsAddress = clientAddress;
                        connectingClientsName = clientName;
                        connectingClientPort = clientPort;
                        string message = "0000" + to_string(nextClientID);
                        SendMessageTo(clientAddress, clientPort, message);
                    }
                    else if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
                        string message = "0000" + to_string(nextClientID);
                        SendMessageTo(clientAddress, clientPort, message);
                    }
                }
            }
            if (inData.substr(0,4) == "0001") {
                if (!connectingAClient) {
                    return;
                }
                if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
                    string clientName = inData.substr(4);
                    if (clientName == connectingClientsName) {
                        connectingAClient = false;
                        nextClientID++;
                        connectedClients->push_back(new ConnectedClient(connectingClientsAddress, clientName, connectingClientPort));
                        connectingClientsAddress = nullptr;
                        cout << "Successfully connected client with ID: " << (nextClientID - 1) << endl;
                    }
                }
            }
            if (inData.substr(0, 4) == "0002") {
                //other stuff
            }
            SDLNet_DestroyDatagram(incoming);
        }
        else {
            break;
        }
    }
}
void Server::Update() {
    ProcessIncoming();
}

ConnectedClient::ConnectedClient(SDLNet_Address* pAddress, string pClientName, int pClientPort)
{
    address = pAddress;
    clientName = pClientName;
    clientPort = pClientPort;
}
