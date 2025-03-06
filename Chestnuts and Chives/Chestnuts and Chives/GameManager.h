#pragma once
#include "GameState.h"
#include <stack>
using namespace std;
class GameManager
{
private:
	stack<GameState*> gameStates;
};

