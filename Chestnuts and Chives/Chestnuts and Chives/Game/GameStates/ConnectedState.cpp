#include "ConnectedState.h"
#include "MapGameplayState.h"
void ConnectedState::ManageInput(SDL_Event* e)
{
	if (currentState == nullptr) {
		return;
	}
	currentState->ManageInput(e);
}

void ConnectedState::ProcessServerMessage(NetworkMessage* msg)
{
	switch (msg->GetMessageType()) {
	case GameStateSync:
		SyncGameState(msg);
		break;
	default:
		if (currentState != nullptr) {
			currentState->ProcessServerMessage(msg);

		}
		break;
	}

}

void ConnectedState::UpdateState(GameplayState* newState)
{
	delete currentState;
	currentState = newState;
	currentState->Initialize(manager);
}

ConnectedState::ConnectedState()
{
	currentState = nullptr;
	manager = nullptr;
}

void ConnectedState::Render(Renderer* renderer)
{
	if (currentState == nullptr) {
		return;
	}
	currentState->Render(renderer);
}

void ConnectedState::Update(int frameTime)
{
	if (currentState == nullptr) {
		return;
	}
	currentState->Update(frameTime);
}

void ConnectedState::Initialize(GameManager* gameManager)
{
	manager = gameManager;
}
void ConnectedState::SyncGameState(NetworkMessage* msg) {
	string messageData = msg->GetExtraData();
	if (currentState != nullptr) {
		if (messageData.substr(12,4) == currentState->GetStateCode()) {
			//server's state is the same as this machine's state, no change needed
			return;
		}

	}
	if (messageData.size() != 20) {
		cout << "suspicious message data size, data: " << messageData << endl;
	}
	int requestedState = NetworkUtilities::IntFromBinaryString(messageData.substr(12, 4), 1);
	//TODO switch to corresponding state
	ServerStates newState = (ServerStates)requestedState;
	switch (requestedState) {
	case TestState:
		UpdateState(new TestGameplayState());
		break;
	case MapState:
		UpdateState(new MapGameplayState());
		break;
	}
}
