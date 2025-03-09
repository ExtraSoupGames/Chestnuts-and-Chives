#include "Client.h"
Client::Client(int portToUse, GameManager* manager) {
    clientID = 0;
    port = portToUse;
    socket = nullptr;
    connectedServer = nullptr;
    gameManager = manager;
}
void Client::ConnectToServer(string serverAddress)
{
    connectedServer = SDLNet_ResolveHostname(serverAddress.c_str());
    SDLNet_WaitUntilResolved(connectedServer, 1000);
    socket = SDLNet_CreateDatagramSocket(connectedServer, port);
}
void Client::ProcessIncoming() {
    NetworkMessage* message = nullptr;
    while (NetworkUtilities::GetNextIncoming(socket, message)) {
        if (message->GetMessageType() == Connect) {
            clientID = NetworkUtilities::IntFromBinaryString(message->GetExtraData(), 1);
            NetworkUtilities::SendMessageTo(ConnectConfirm, "", socket, connectedServer, 66661);

            gameManager->Initialize();
        }
        delete message;
    }
}
void Client::Update() {
    if (connectedServer == nullptr) {
        return;
    }
    ProcessIncoming();
    if (clientID == 0) {
        //if the client ID is 0 then this client has not yet connected to the server
        NetworkUtilities::SendMessageTo(Connect, "", socket, connectedServer, 66661);
        return;
    }
    string message = NetworkUtilities::AsBinaryString(1, clientID);
    NetworkUtilities::SendMessageTo(Heartbeat, message, socket, connectedServer, 66661);
    gameManager->Update();
}

bool Client::IsConnected()
{
    return connectedServer != nullptr;
}

void Client::Render(SDL_Renderer* renderer)
{
    if (!IsConnected()) {
        return;
    }
    gameManager->Render();
}
