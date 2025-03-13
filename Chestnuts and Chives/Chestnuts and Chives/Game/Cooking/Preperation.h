#pragma once
#include <string>
using namespace std;
class Preperation {
public:
//Gets the Prefix to be put in front of the ingredient when this preperation has been done to that ingredient
	virtual string GetIngredientPrefix() = 0;
};