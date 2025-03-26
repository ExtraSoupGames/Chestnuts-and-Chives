#include "MapServerState.h"
#include "TestServerState.h"
#include "Server.h"
MapServerState::MapServerState(Server* server, int players) : ServerStateVotable(server, players)
{
}

void MapServerState::Update(int frameTime)
{
	ServerState::UpdateSyncBroadcasts(frameTime);
}

void MapServerState::OnExit()
{
}

void MapServerState::OnEnter()
{
}

void MapServerState::ProcessIncoming(NetworkMessage* incomingMessage)
{
	if (incomingMessage->GetMessageType() == GameStateSync) {
		ServerStateVotable::ProcessVoteMessage(incomingMessage->GetExtraData() == "1");
	}
}

void MapServerState::AllPlayersVoted()
{
	server->SwitchState(new TestServerState(server, votesNeeded));
}

string MapServerState::GetStateCode()
{
	return "0001";
}
