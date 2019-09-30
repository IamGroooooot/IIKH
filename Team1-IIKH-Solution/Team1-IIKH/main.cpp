#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"
#include "Exception.h"
#include "Greeter.h"

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	/********** Variables **********/
	PlanDB planDB;
	RecipeDB recipeDB;
	std::vector<std::string> menu;
	Greeter greeter(menu, recipeDB, planDB);
	/*******************************/

	while (true)
	{
		// clear screen
		system("CLS");
		// print the menu for IIKH
		greeter.printMenu();
		// select menu and update the screen to selected menu
		greeter.selectMenu();

		// waits for user to continue
		system("pause");
		//std::cout << "Press anykey to continue" << endl;
		//std::cout << "" << std::flush;
		//getchar();
		//getchar();
	}
	return 0;


	try {
		RecipeDB recipeDB;
		for (auto record : recipeDB._search(std::string("RecipeN")))
			recipeDB._show(record);
		recipeDB._show(std::string("sfda"));
	}
	catch (Exception & e) {
		e.resolve();
	}
}