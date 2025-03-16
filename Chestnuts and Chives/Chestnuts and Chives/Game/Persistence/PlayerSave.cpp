#include "PlayerSave.h"

PlayerSave::PlayerSave()
{
    items.push_back(ItemSave());
}

string PlayerSave::GetSaveData()
{
    string playerData = "Player:";
    string itemData;
    for (int i = 0; i < items.size(); i++) {
        if (i != 0) itemData.append("\n");
        itemData.append(items.at(i).GetSaveData());
    }
    return playerData.append("\n" + itemData);;
}
