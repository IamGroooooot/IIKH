#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"

int main() {
	PlanDB planDB;
	RecipeDB recipeDB;


	cout << "------Print My Meal Plans------" << endl;
	planDB._showAll();
	cout << "------Print My Recipes------" << endl;
	recipeDB._showAll();
	/*
	try {
		Recipe* recipeElement1 = new Recipe(std::string("���Ǥ���� ���ִ� ������ 1"), std::string("�̳� ���ְ� �����."), 100, {std::string("���1"), std::string("���2") });
		recipeDB._insert(std::string("insert 1"), *recipeElement1);
		Recipe* recipeElement2 = new Recipe(std::string("����Ӹ����� ������2"), std::string("�̳� ������ �����."), 10, { std::string("���1123"), std::string("���2123") });
		recipeDB._insert(std::string("insert 2"), *recipeElement2);
		recipeDB._showAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	try {
		planDB._insert(Date(2019, 8, 28), Plan(std::string("��� "), Date(2019, 8, 28), {
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		planDB._insert(Date(2019, 8, 30), Plan(std::string("���3"), Date(2019, 8, 30), {
			Meal({ std::string("��"), std::string("��� �Ķ���") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		planDB._insert(Date(2019, 8, 29), Plan(std::string("���2"), Date(2019, 8, 29), {
			Meal({ std::string("��"), std::string("��") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		planDB._insert(Date(2019, 8, 31), Plan(std::string("���4"), Date(2019, 8, 31), {
			Meal({ std::string("������ġ") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		planDB._select(Date(2019, 8, 31));
		//plan._showAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	std::cout << "----------------File �ҷ����� Test----------------" << std::endl;
	
	std::vector<std::map<std::string, std::string>*> parsedData = CSVParser::instance().read("IIKHRecipe.csv");

	for (int i = 0; i < parsedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = parsedData[i];
		for (auto it = temp->cbegin(); it != temp->cend(); ++it)
		{
			std::cout << it->first << " | " << it->second << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "----------------���̺굥��Ÿ ���� Test----------------" << std::endl;

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
	*/
}