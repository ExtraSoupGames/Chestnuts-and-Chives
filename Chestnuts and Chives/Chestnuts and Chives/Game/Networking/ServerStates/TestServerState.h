#pragma once
#include "ServerStateVotable.h"
class TestServerState : public ServerStateVotable {
private:
	int frameTimer;
protected:
public:
	TestServerState(Server* server, int players);
	virtual void Update(int frameTime) override;
	virtual void OnExit() override;
	virtual void OnEnter() override;
	virtual void ProcessIncoming(NetworkMessage* incomingMessage) override;
	virtual void AllPlayersVoted() override;
	virtual string GetStateCode() override;
};