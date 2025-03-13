#include "Ingredient.h"

string Ingredient::GetName()
{
    string out;
    if (prep2) {
        out += prep2->GetIngredientPrefix();
    }
    if (prep1) {
        out += prep1->GetIngredientPrefix();
    }
    out += BaseIngredientName();
    return out;
}

void Ingredient::ApplyPreperation(Preperation* prep)
{
    if (prep1 == nullptr) {
        prep1 = prep;
        return;
    }
    if (prep2 == nullptr) {
        prep2 = prep;
        return;
    }
}
