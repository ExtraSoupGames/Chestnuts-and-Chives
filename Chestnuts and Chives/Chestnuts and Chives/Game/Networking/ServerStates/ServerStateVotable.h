#pragma once
#include "ServerState.h"
class ServerStateVotable : public ServerState {
private:
	int currentVotes;
	int votesNeeded;
protected:
public:
	ServerStateVotable(int playerCount);
	virtual void ProcessVoteMessage(bool IsPositiveVote) override;
	virtual void AllPlayersVoted() = 0;
};