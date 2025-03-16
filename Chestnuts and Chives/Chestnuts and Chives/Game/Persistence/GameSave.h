#pragma once
#include "PlayerSave.h"
#include <vector>
#include <string>
using namespace std;
class GameSave {
	vector<PlayerSave> players;
public:
	string GetSaveData();

};