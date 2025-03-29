#include "Server.h"
#include "MapServerState.h"
Server::Server(string addressIP) {
    address = SDLNet_ResolveHostname(addressIP.c_str());
    if (address == nullptr) {
        std::cout << ("Address is invalid!") << std::endl;
    }
    //block until the address gets resolved, wait indefinitely
    SDLNet_WaitUntilResolved(address, -1);
    socket = SDLNet_CreateDatagramSocket(address, 66661);
    if (!socket) {
        printf("Failed to create UDP socket: %s\n", SDL_GetError());
    }
    SDLNet_SimulateDatagramPacketLoss(socket, 99);
    nextClientID = 1;
    connectingAClient = false;
    connectingClientsAddress = nullptr;
    connectedClients = new vector<ConnectedClient*>();
    connectingClientPort = 0;
    sender = new ServerMessageSender(socket, *connectedClients);

    save = nullptr;
    state = nullptr;

    lastTicks = SDL_GetTicks();
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
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
            TryConnectClient(message->GetExtraData(), message->GetAddress(), message->GetPort());
            break;
        case ConnectConfirm:
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
            ConfirmClientConnection(message->GetAddress());
            break;
        case GameStateSync:
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
            if (state != nullptr) {
                state->ProcessVoteMessage(message);
            }
            break;
        case Test:
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
            break;
        case ImportantMessageConfirmation:
            sender->ConfirmationRecieved(message);
            break;
        default:
            if (state != nullptr) {
                state->ProcessIncoming(message);
            }
        }
        delete message;
    }
}
void Server::Broadcast(string message)
{
    for (int i = 0; i < connectedClients->size(); i++) {
        ConnectedClient* c = connectedClients->at(i);
        NetworkUtilities::SendMessageTo(GameStateSync, message, socket, c->address, c->clientPort);
    }
}
void Server::ImportantBroadcast(NetworkMessageTypes type, string message)
{
    if (!sender) {
        cout << "Sender is null" << endl;
    }
    sender->BroadcastImportantMessage(type, message);
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
        sender->NewClientConnected(connectedClients->at(connectedClients->size() - 1));
        sender->SendImportantMessage(GameStateSync, state->GetStateCode(), new ConnectedClient(connectingClientsAddress, connectingClientPort));
        connectingClientsAddress = nullptr;
        cout << "Successfully connected client with ID: " << (nextClientID - 1) << endl;
    }
}
void Server::TryConnectClient(string inData, SDLNet_Address* clientAddress, int clientPort)
{
    inData = inData.substr(12);

    if (!IsAlreadyConnected(clientAddress, clientPort)) {
        if (!connectingAClient) {
            connectingAClient = true;
            connectingClientsAddress = clientAddress;
            connectingClientPort = clientPort;
            string message = NetworkUtilities::AsBinaryString(1, nextClientID);
            sender->SendImportantMessage(Connect, message, new ConnectedClient(clientAddress, clientPort));
        }
        else if (SDLNet_GetAddressString(clientAddress) == SDLNet_GetAddressString(connectingClientsAddress)) {
            if (clientPort == connectingClientPort) {
                string message = NetworkUtilities::AsBinaryString(1, nextClientID);
                sender->SendImportantMessage(Connect, message, new ConnectedClient(clientAddress, clientPort));
            }
        }
    }
}
void Server::Update() {
    int updateTime = SDL_GetTicks() - lastTicks;
    lastTicks = SDL_GetTicks();
    ProcessIncoming();
    sender->SendUnsentMessages(false);
    if (state != nullptr) {
        state->Update(updateTime);
    }
    else {
        SwitchState(new MapServerState(this));
    }
}

int Server::GetPlayerCount()
{
    return connectedClients->size();
}

void Server::SwitchState(ServerState* newState)
{
    if (state != nullptr) {
        state->OnExit();
    }
    delete state;
    state = newState;
    newState->OnEnter();
    ImportantBroadcast(GameStateSync, newState->GetStateCode());
}
