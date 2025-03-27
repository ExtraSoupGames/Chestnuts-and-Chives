#pragma once
#include "ServerStateVotable.h"
class MapServerState : public ServerStateVotable {
private:
protected:
public:
	MapServerState(Server* server);
	virtual ~MapServerState() override;
	virtual void Update(int frameTime) override;
	virtual void OnExit() override;
	virtual void OnEnter() override;
	virtual void ProcessIncoming(NetworkMessage* incomingMessage) override;
	virtual void AllPlayersVoted() override;
	virtual string GetStateCode() override;
};