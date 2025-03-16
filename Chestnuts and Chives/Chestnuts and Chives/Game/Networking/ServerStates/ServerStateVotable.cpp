#include "ServerStateVotable.h"
ServerStateVotable::ServerStateVotable(int playerCount)
{
	currentVotes = 0;
	votesNeeded = playerCount;
}

void ServerStateVotable::ProcessVoteMessage(bool IsPositiveVote)
{
	currentVotes += IsPositiveVote ? 1 : 0;
	if (currentVotes >= votesNeeded) {
		AllPlayersVoted();
	}

}
