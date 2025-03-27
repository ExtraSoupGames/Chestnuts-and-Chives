#pragma once
#include "ServerState.h"
class ConnectedClient;
class ServerStateVotable : public ServerState {
private:
	//Clients that have voted to move to next state
	vector<ConnectedClient*> confirmedClients;
protected:
public:
	ServerStateVotable(Server* server);
	virtual ~ServerStateVotable() override;
	virtual void ProcessVoteMessage(NetworkMessage* msg) override;
	virtual void AllPlayersVoted() = 0;
};