#include "ServerStateVotable.h"
ServerStateVotable::ServerStateVotable(Server* server, int playerCount) : ServerState(server)
{
	currentVotes = 0;
	votesNeeded = playerCount;
}

void ServerStateVotable::ProcessVoteMessage(bool IsPositiveVote)
{
	cout << "Vote received" << endl;
	currentVotes += IsPositiveVote ? 1 : 0;
	if (currentVotes >= votesNeeded) {
		cout << "all votes received" << endl;
		AllPlayersVoted();
	}

}
