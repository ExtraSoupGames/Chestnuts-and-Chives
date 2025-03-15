#include "Ingredient.h"
#include <fstream>
#include <iostream>
#include "SDL3/SDL.h"
vector<Ingredient*> IngredientHelper::GetIngredients(string jsonData)
{
    json data = json::parse(jsonData);
    std::cout << data.begin().value() << std::endl;
    return vector<Ingredient*>();
}

vector<Ingredient*> IngredientHelper::GetAllIngredients()
{
    string ingredientsFile;
    char* fileIn = (char*)SDL_LoadFile("Assets/GameData/Ingredients.json", NULL);
    ingredientsFile = fileIn;
    return GetIngredients(ingredientsFile);
}
