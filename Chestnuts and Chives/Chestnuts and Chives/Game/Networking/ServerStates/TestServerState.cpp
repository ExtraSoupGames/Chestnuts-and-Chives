#include "TestServerState.h"
#include "Server.h"
#include "MapServerState.h"
TestServerState::TestServerState(Server* server, int playerCount) : ServerStateVotable(server, playerCount)
{
	frameTimer = 0;
}

void TestServerState::Update(int frameTime)
{
	ServerState::UpdateSyncBroadcasts(frameTime);
}

void TestServerState::OnExit()
{
}

void TestServerState::OnEnter()
{
}

void TestServerState::ProcessIncoming(NetworkMessage* incomingMessage)
{
	if (incomingMessage->GetMessageType() == GameStateSync) {
		ServerStateVotable::ProcessVoteMessage(incomingMessage->GetExtraData() == "1");
	}
}

void TestServerState::AllPlayersVoted()
{
	server->SwitchState(new MapServerState(server, votesNeeded));
}
string TestServerState::GetStateCode() {
	return "0000";
}