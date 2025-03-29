#include "ServerStateVotable.h"
#include <algorithm>
#include "Server.h"
ServerStateVotable::ServerStateVotable(Server* server) : ServerState(server)
{

}

ServerStateVotable::~ServerStateVotable()
{
	for (auto c : confirmedClients) {
		delete c;
	}
}

void ServerStateVotable::ProcessVoteMessage(NetworkMessage* msg)
{
	//remove any previous votes from this client
	confirmedClients.erase(remove_if(confirmedClients.begin(), confirmedClients.end(),
		[msg](ConnectedClient* c)
		{return SDLNet_GetAddressString(c->address) == SDLNet_GetAddressString(msg->GetAddress()) && c->clientPort == msg->GetPort(); }), confirmedClients.end());
	//add a vote if they voted positively
	if (msg->GetExtraData().substr(12,1) == "1") {
		confirmedClients.push_back(new ConnectedClient(msg->GetAddress(), msg->GetPort()));
	}
	//check if all players have voted
	if (confirmedClients.size() == server->GetPlayerCount()) {
		AllPlayersVoted();
	}
}
