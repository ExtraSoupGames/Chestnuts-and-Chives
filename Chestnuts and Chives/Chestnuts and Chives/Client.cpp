#include "Client.h"
void Client::SendMessage()
{
    const char* message = "Hello, from the client!";
    SDLNet_SendDatagram(socket, connectedServer->GetAddress(), 66661, message, strlen(message));
}
Client::Client(Server* s) {
	connectedServer = s;
	socket = SDLNet_CreateDatagramSocket(connectedServer->GetAddress(), 66662);
}
void Client::Update() {
    SendMessage();
    SDLNet_Datagram* incoming;
    if (SDLNet_ReceiveDatagram(socket, &incoming)) {
        if (incoming) {
            printf("Received from %s:%d - %s\n", SDLNet_GetAddressString(incoming->addr), incoming->port, (char*)incoming->buf);
            SDLNet_DestroyDatagram(incoming);
        }
    }
}