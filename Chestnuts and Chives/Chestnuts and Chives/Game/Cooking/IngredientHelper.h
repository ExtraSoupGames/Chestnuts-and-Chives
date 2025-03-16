#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "SDL3/SDL.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Ingredient;
class IngredientHelper {
	static vector<Ingredient*> GetIngredients(string jsonData);
public:
	static vector<Ingredient*> GetAllIngredients();
};