#pragma once
#include "GameState.h"
#include "GameplayState.h"
#include "NetworkUtilities.h"
#include "ServerState.h"
#include "TestGameplayState.h"
#include "Client.h"
//this state should be active whenever the client is connected to a server
//it should represen an FSM to stay in sync with the server's serverStates
//It should also handle staying connected with the server (Maintaining a heartbeat)
class ConnectedState : public GameState {
private:
	GameplayState* currentState;
	Client* manager;
	void UpdateState(GameplayState* newState);
	void SyncGameState(NetworkMessage* msg);
protected:
public:
	ConnectedState();
	virtual void Render(Renderer* renderer) override;
	virtual void Update(int frameTime) override;
	virtual void Initialize(Client* manager) override;
	virtual void ManageInput(SDL_Event* e) override;
	virtual void ProcessServerMessage(NetworkMessage* msg) override;
};