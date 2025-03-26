#pragma once
#include "ServerState.h"
class ServerStateVotable : public ServerState {
private:
	int currentVotes;
protected:
	int votesNeeded;
public:
	ServerStateVotable(Server* server, int playerCount);
	virtual void ProcessVoteMessage(bool IsPositiveVote) override;
	virtual void AllPlayersVoted() = 0;
};