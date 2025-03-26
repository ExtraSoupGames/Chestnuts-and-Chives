#include "ServerState.h"
#include "Server.h"
void ServerState::UpdateSyncBroadcasts(int frameTime)
{
	syncBroadcastTimer += frameTime;
	if (syncBroadcastTimer > syncBroadcastRate) {
		syncBroadcastTimer -= syncBroadcastRate;
		server->Broadcast(GetStateCode());
	}
}

ServerState::ServerState(Server* gameServer)
{
	syncBroadcastTimer = 0;
	syncBroadcastRate = 1000;
	server = gameServer;
}
