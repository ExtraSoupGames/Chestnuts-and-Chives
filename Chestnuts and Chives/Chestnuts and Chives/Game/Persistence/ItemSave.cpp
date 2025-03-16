#include "ItemSave.h"

ItemSave::ItemSave()
{
    ID = 1;
    count = 3;
}

string ItemSave::GetSaveData()
{
    string out = "ItemID:" + to_string(ID);
    out.append("\nItemCount:" + to_string(count));
    return out;
}
