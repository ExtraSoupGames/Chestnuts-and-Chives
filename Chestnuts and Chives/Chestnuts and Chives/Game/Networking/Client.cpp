#include "Client.h"
Client::Client(int portToUse, string windowName) {
    clientID = 0;
    port = portToUse;
    socket = nullptr;
    connectedServer = nullptr;
    renderer = new Renderer(windowName);
    gameManager = new GameManager(renderer);
    gameServer = nullptr;
}
void Client::ConnectToServer(string serverAddress)
{
    connectedServer = SDLNet_ResolveHostname(serverAddress.c_str());
    SDLNet_WaitUntilResolved(connectedServer, 1000);
    socket = SDLNet_CreateDatagramSocket(connectedServer, port);
}
void Client::CreateAndConnectToServer(string serverAddress)
{
    gameServer = new Server(serverAddress);
    ConnectToServer(serverAddress);
    sender = new ClientMessageSender(socket, connectedServer, 66661);
}
void Client::ProcessIncoming() {
    NetworkMessage* message = nullptr;
    while (NetworkUtilities::GetNextIncoming(socket, message)) {
        if (message->GetMessageType() == Connect) {
            clientID = NetworkUtilities::IntFromBinaryString(message->GetExtraData(), 1);
            NetworkUtilities::SendMessageTo(ConnectConfirm, "", socket, connectedServer, 66661);

            gameManager->Initialize();
        }
        if (message->GetMessageType() == GameStateChange){
            int gameState = NetworkUtilities::IntFromBinaryString(message->GetExtraData(), 1);
            //gameManager->SwitchState();
        }
        if (message->GetMessageType() == Test) {
            sender->SendImportantMessageConfirmation(message);
            std::cout << "Client has received an important message" << endl;
        }
        if (message->GetMessageType() == ImportantMessageConfirmation) {
            sender->ConfirmationRecieved(message);
            cout << "Client has received an important message confirmation" << endl;
        }
        delete message;
    }
}
void Client::Update() {
    if (gameServer != nullptr) {
        gameServer->Update();
    }
    if (connectedServer == nullptr) {
        return;
    }
    ProcessIncoming();
    if (clientID == 0) {
        //if the client ID is 0 then this client has not yet connected to the server
        NetworkUtilities::SendMessageTo(Connect, "", socket, connectedServer, 66661);
        return;
    }
    //string message = NetworkUtilities::AsBinaryString(1, clientID);
    //NetworkUtilities::SendMessageTo(Heartbeat, message, socket, connectedServer, 66661);
    gameManager->Update();
    sender->SendUnsentMessages();
}

bool Client::IsConnected()
{
    return connectedServer != nullptr;
}

void Client::Render()
{
    if (!IsConnected()) {
        return;
    }
    gameManager->Render();
}

void Client::ManageInput(SDL_Event* e)
{
    gameManager->ManageInput(e);
    if (e->type == SDL_EVENT_KEY_UP) {
        sender->SendImportantMessage(Test, "1111");
    }
    if (e->type == SDL_EVENT_KEY_DOWN) {
        gameServer->SendTestMessage();
    }
}
