#pragma once
#include <vector>
#include <string>
#include "NetworkUtilities.h"
using namespace std;
class Server;
class ServerState {
private:
protected:
public:
	virtual void Update(Server* server) = 0;
	virtual void OnExit() = 0;
	virtual void OnEnter() = 0;
	virtual void ProcessIncoming(NetworkMessage* incomingMessage) = 0;

	virtual void ProcessVoteMessage(bool IsPositiveVote) = 0;
};
