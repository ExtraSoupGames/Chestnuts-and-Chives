#include "TestServerState.h"
#include "Server.h"
#include "MapServerState.h"
TestServerState::TestServerState(Server* server) : ServerStateVotable(server)
{
	frameTimer = 0;
}

TestServerState::~TestServerState()
{
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
		ServerStateVotable::ProcessVoteMessage(incomingMessage);
	}
}

void TestServerState::AllPlayersVoted()
{
	server->SwitchState(new MapServerState(server));
}
string TestServerState::GetStateCode() {
	return "0000";
}