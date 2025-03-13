#pragma once
#include <vector>
#include "Preperation.h"
#include <string>
using namespace std;
class Ingredient {
private:
	Preperation* prep1;
	Preperation* prep2;
protected:
	virtual string BaseIngredientName() = 0;
public:
	string GetName();
	void ApplyPreperation(Preperation* prep);
};