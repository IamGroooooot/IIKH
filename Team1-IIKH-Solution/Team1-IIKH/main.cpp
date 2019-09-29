#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"
#include "Greeter.h"

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	PlanDB planDB;
	RecipeDB recipeDB;
	std::vector<std::string> menu;
	Greeter greeter(menu, recipeDB, planDB);


	while (true)
	{
		system("CLS");
		greeter.printMenu();
		greeter.selectMenu();

		std::cout << "Press anykey to continue" << endl;
		std::cout << "" << std::flush;
		getchar();
		getchar();
	}
}