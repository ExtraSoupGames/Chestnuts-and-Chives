#pragma once
#include "ServerStateVotable.h"
class MapServerState : public ServerStateVotable {
private:
protected:
public:
	virtual void Update(Server* server) override;
	virtual void OnExit() override;
	virtual void OnEnter() override;
	virtual void ProcessIncoming(NetworkMessage* incomingMessage) override;
};