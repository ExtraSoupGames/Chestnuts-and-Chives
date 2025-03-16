#include "GameSave.h"

string GameSave::GetSaveData()
{

	players.push_back(PlayerSave());
	string gameData;
	//populate gameData
	gameData = "GameData:";
	string playerData;
	for (int i = 0; i < players.size(); i++) {
		playerData.append(players.at(i).GetSaveData());
	}
	return gameData.append("\n" + playerData);
}
