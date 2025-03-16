#pragma once
#include <vector>
#include <string>
using namespace std;
class Ingredient {
private:
protected:
	virtual string BaseIngredientName() = 0;
public:
	virtual string GetName() = 0;
	virtual int GetScoreModifier() = 0;
};