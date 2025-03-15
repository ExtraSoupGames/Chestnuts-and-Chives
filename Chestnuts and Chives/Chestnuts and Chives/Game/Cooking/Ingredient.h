#pragma once
#include <vector>
#include <string>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Ingredient {
private:
protected:
	virtual string BaseIngredientName() = 0;
public:
	virtual string GetName() = 0;
	virtual int GetScoreModifier() = 0;
};
class IngredientHelper {
	static vector<Ingredient*> GetIngredients(string jsonData);
public:
	static vector<Ingredient*> GetAllIngredients();
};