#include "Pan.h"

void Pan::ProgressCooking(vector<Ingredient*> stageIngredients)
{
	if (cookingStage != ReadyToCook || cookingStage == Stage1 || cookingStage == Stage2) {
		return;
	}
	//progress the cooking stage by 1 and add the used ingredients to the respective stage in storage
	vector<Ingredient*>* ingredientTarget;
	switch (cookingStage) {
	case ReadyToCook:
		ingredientTarget = &stage1Ingredients;
		cookingStage = Stage1;
		break;
	case Stage1:
		ingredientTarget = &stage2Ingredients;
		cookingStage = Stage2;
		break;
	case Stage2:
		ingredientTarget = &stage3Ingredients;
		cookingStage = Stage3;
		break;
	}
}
