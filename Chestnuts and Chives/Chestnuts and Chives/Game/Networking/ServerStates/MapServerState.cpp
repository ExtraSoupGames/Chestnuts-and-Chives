#include "MapServerState.h"
#include "TestServerState.h"
#include "Server.h"
MapServerState::MapServerState(Server* server) : ServerStateVotable(server)
{
}

MapServerState::~MapServerState()
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
		ServerStateVotable::ProcessVoteMessage(incomingMessage);
	}
}

void MapServerState::AllPlayersVoted()
{
	server->SwitchState(new TestServerState(server));
}

string MapServerState::GetStateCode()
{
	return "0001";
}
