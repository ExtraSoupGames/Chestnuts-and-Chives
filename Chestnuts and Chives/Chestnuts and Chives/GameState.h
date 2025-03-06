#pragma once
//Forward declaration
class GameManager;

class GameState
{
public:
	virtual void Update(float frameTime) = 0;
	virtual void Initialize(GameManager* manager) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Exit() = 0;
};
class BaseGameState : GameState
{
public:

};

