#pragma once
#include <vector>
#include <string>
#include "Dish.h"
#include "Ingredient.h"


class Pan {
private:
	vector<Ingredient*> stage1Ingredients;
	vector<Ingredient*> stage2Ingredients;
	vector<Ingredient*> stage3Ingredients;
	//ready to cook, stage1 and stage 2 and stage 3 must be sequential here
	enum CookingStage {
		Unstarted = 0,
		ReadyToCook = 1,
		Stage1 = 2,
		Stage2 = 3,
		Stage3 = 4,
		Finished = 5
	};
	CookingStage cookingStage;
public:
	void ProgressCooking(vector<Ingredient*> stageIngredients);
};