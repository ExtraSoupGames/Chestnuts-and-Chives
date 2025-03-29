#include "Client.h"
Client::Client(int portToUse, string windowName) {
    clientID = 0;
    port = portToUse;
    socket = nullptr;
    connectedServer = nullptr;
    renderer = new Renderer(windowName);
    gameManager = new GameManager(renderer, this);
    gameManager->Initialize();
    gameServer = nullptr;
    sender = nullptr;
}
void Client::ConnectToServer(string serverAddress)
{
    if (connectedServer != nullptr) {
        cout << "Already connected to as server!" << endl;
    }
    connectedServer = SDLNet_ResolveHostname(serverAddress.c_str());
    SDLNet_WaitUntilResolved(connectedServer, 1000);
    socket = SDLNet_CreateDatagramSocket(connectedServer, port);
    SDLNet_SimulateDatagramPacketLoss(socket, 99);

    if (!socket) {
        cout << "Invalid socket" << SDL_GetError() << endl;
    }
    sender = new ClientMessageSender(socket, connectedServer, 66661);
}
void Client::CreateServer(string serverAddress)
{
    if (gameServer != nullptr) {
        cout << "Already created a server!" << endl;
        return;
    }
    gameServer = new Server(serverAddress);
}
void Client::ProcessIncoming() {
    NetworkMessage* message = nullptr;
    while (NetworkUtilities::GetNextIncoming(socket, message)) {
        if (message->GetMessageType() == Connect) {
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
            clientID = NetworkUtilities::IntFromBinaryString(message->GetExtraData().substr(12), 1);
            sender->SendImportantMessage(ConnectConfirm, "");
        }
        if (message->GetMessageType() == ImportantMessageConfirmation) {
            sender->ConfirmationRecieved(message);
        }
        if (message->GetMessageType() == Test) {
            if (!sender->SendImportantMessageConfirmation(message)) {
                return;
            }
        }
        else {
            gameManager->ProcessServerMessage(message);
        }
        delete message;
    }
}
void Client::Update() {
    gameManager->Update();
    if (gameServer != nullptr) {
        gameServer->Update();
    }
    if (IsConnected()) {
        ProcessIncoming();
        if (clientID == 0) {
            sender->SendImportantMessage(Connect, "");
            connectAttempted = true;
        }
    }
    if (sender != nullptr) {
        sender->SendUnsentMessages(false);
    }
}

bool Client::IsConnected()
{
    return connectedServer != nullptr;
}

void Client::Render()
{
    gameManager->Render();
}

void Client::ManageInput(SDL_Event* e)
{
    gameManager->ManageInput(e);
}

void Client::SendServerMessage(NetworkMessageTypes type, string msg)
{
    NetworkUtilities::SendMessageTo(type, msg, socket, connectedServer, 66661);
}

void Client::SendImportantServerMessage(NetworkMessageTypes type, string message)
{
    sender->SendImportantMessage(type, message);
}

bool Client::SendImportantMessageConfirmation(NetworkMessage* msg)
{
    return sender->SendImportantMessageConfirmation(msg);
}
