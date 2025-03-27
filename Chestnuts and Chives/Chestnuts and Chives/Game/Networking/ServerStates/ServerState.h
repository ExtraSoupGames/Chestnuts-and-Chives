#pragma once
#include <vector>
#include <string>
#include "NetworkUtilities.h"
using namespace std;
enum ServerStates {
	TestState,
	MapState
};
class Server;
class ServerState {
private:
	int syncBroadcastRate;
	int syncBroadcastTimer;
protected:
	Server* server;
	//call this in each Update override to send sync messages to clients
	void UpdateSyncBroadcasts(int frameTime);
public:
	ServerState(Server* server);
	virtual ~ServerState() = default;
	virtual void Update(int frameTime) = 0;
	virtual void OnExit() = 0;
	virtual void OnEnter() = 0;
	virtual void ProcessIncoming(NetworkMessage* incomingMessage) = 0;

	virtual void ProcessVoteMessage(NetworkMessage* msg) = 0;
	virtual string GetStateCode() = 0;
};
