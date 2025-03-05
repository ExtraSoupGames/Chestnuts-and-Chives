#include "Server.h"
void Server::SendMessage()
{
    const char* message = "Hello from the server!";
    SDLNet_SendDatagram(socket, clientAddress, 66662, message, strlen(message));

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
    clientAddress = nullptr;
}
void Server::Update() {
    SDLNet_Datagram* incoming;
    if (SDLNet_ReceiveDatagram(socket, &incoming)) {
        if (incoming) {
            printf("Received from %s:%d - %s\n", SDLNet_GetAddressString(address), incoming->port, (char*)incoming->buf);
            clientAddress = SDLNet_RefAddress(incoming->addr);
            SendMessage();
            SDLNet_DestroyDatagram(incoming);
        }
    }
}
SDLNet_Address* Server::GetAddress() {
	return address;
}
