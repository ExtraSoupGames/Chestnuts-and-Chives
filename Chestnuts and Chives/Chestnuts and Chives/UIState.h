#pragma once
#include "GameState.h"
#include "UIElement.h"
#include <vector>
using namespace std;
class UIState : GameState
{
private:
	vector<UIElement*> elements;
};

