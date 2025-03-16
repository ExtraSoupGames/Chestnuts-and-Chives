#pragma once
#include <vector>
#include <string>
#include "ItemSave.h"
using namespace std;
class PlayerSave {
	vector<ItemSave> items;
public:
	PlayerSave();
	string GetSaveData();
};