#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"

int main() {
	PlanDB plan;
	RecipeDB recipeDB;
	CSVParser parser;

	try {
		Recipe* recipeElement1 = new Recipe(std::string("Á¶¤Ç¤©¶ó°Ô ¸ÀÀÖ´Â ·¹½ÃÇÇ 1"), std::string("°Ì³ª ¸ÀÀÖ°Ô ¸¸µç´Ù."), 100, {std::string("Àç·á1"), std::string("Àç·á2") });
		recipeDB._insert(std::string("insert 1"), *recipeElement1);
		Recipe* recipeElement2 = new Recipe(std::string("Á¹¶ó¤Ó¸À¾ø´Â ·¹½ÃÇÇ2"), std::string("°Ì³ª ¸À¾ø°Ô ¸¸µç´Ù."), 10, { std::string("Àç·á1123"), std::string("Àç·á2123") });
		recipeDB._insert(std::string("insert 2"), *recipeElement2);
		recipeDB._showAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	try {
		plan._insert(Date(2019, 8, 28), Plan(std::string("Æò¹ü "), {
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan._insert(Date(2019, 8, 30), Plan(std::string("Æò¹ü3"), {
			Meal({ std::string("¹ä"), std::string("°è¶õ ÈÄ¶óÀÌ") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan._insert(Date(2019, 8, 29), Plan(std::string("Æò¹ü2"), {
			Meal({ std::string("¹ä"), std::string("±¹") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan._insert(Date(2019, 8, 31), Plan(std::string("Æò¹ü4"), {
			Meal({ std::string("»÷µåÀ§Ä¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan._select(Date(2019, 8, 31));
		//plan._showAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	std::cout << "----------------File ºÒ·¯¿À±â Test----------------" << std::endl;
	
	std::vector<std::map<std::string, std::string>*> parsedData = parser.read("IIKHRecipe.csv");

	for (int i = 0; i < parsedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = parsedData[i];
		for (auto it = temp->cbegin(); it != temp->cend(); ++it)
		{
			std::cout << it->first << " | " << it->second << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "----------------¼¼ÀÌºêµ¥ÀÌÅ¸ »ı¼º Test----------------" << std::endl;

	std::vector<std::map<std::string, std::string>*> savedData = recipeDB._setRecipeDBData();
	for (int i = 0; i < savedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = savedData[i];
		for (auto item = temp->cbegin(); item != temp->cend(); ++item)
		{
			std::cout << item->first<<" | "<< item->second << std::endl;
			
		}
		std::cout << std::endl;
	}
	return 0;
}