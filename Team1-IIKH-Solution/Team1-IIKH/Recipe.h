#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"
#include "CSVParser.h"

// stores recipe's name, description, ingredients, time
// and performs action related to recipe and it's member.
class Recipe {
private:
	// Recipe's Name
	std::string name;
	// Recipe's Description
	std::string description;
	// Recipe's Ingredients: it is set of ingredient(we use "string" for ingredient)
	std::set<std::string> ingredients;
	// Recipe's Expected Time it takes to cook. 
	int time;
	// ingredientString for saving(Buffer)
	std::string ingredientString;
public:
	// CTOR: name, description, time, ingredients will be initialized
	Recipe(std::string && n, std::string && d, int t, std::vector<std::string> i) :
		name(n), description(d), time(t), ingredients() {
		// insert all ingredient to ingredients set
		for (std::string s : i)
			ingredients.insert(s);
	};
	
	/* GET */
	// get Recipe name
	const std::string & getName() const { return name; }
	// get Recipe description
	const std::string & getDescription() const { return description; }
	// get Recipe ingredients
	const std::set<std::string> & getIngredients() const { return ingredients; }
	// get Recipe time
	int getTime() const { return time; }

	/* SET */
	// sets Recipe name
	void setName(std::string & n) { name = n; }
	// sets Recipe description
	void setDescription(std::string & d) { description = d; }
	// sets Recipe time
	void setTime(int t) { time = t; }

	/* GET */
	// insert Recipe ingredient to ingredients set. and returns second stored value
	bool addIngredient(std::string & n) { return ingredients.insert(n).second; }
	// remove Recipe ingredient to ingredients set. and returns second stored value
	bool removeIngredient(std::string & n) { return ingredients.erase(n) == 1; }
	// find if there is ingredient
	bool searchIngredient(std::string & n) { return ingredients.find(n) != ingredients.end(); }

	std::string getIngredientsIntoString() {
		for (auto ingredient : ingredients) {
			ingredientString.append(ingredient);
			ingredientString.append("$");
		}

		return ingredientString;
	}
	// print Recipe data
	void print() {
		std::cout << "Recipe Name : " << name << std::endl;
		std::cout << "Ingredients : "<< endl;
		for (std::string s : ingredients) {
			std::cout << " - " << s << std::endl;
		}
		std::cout << "Expected Time : " << time << std::endl;
		std::cout << "Direction : " << std::endl;
		
		for (auto pLines : CSVParser::instance().split(description, '$', -1)) {
			std::cout << " - ";
			int i = 0;
			for (auto pCommas : CSVParser::instance().split(pLines, '/', -1)) {
				if (i == 0) {
					std::cout << pCommas;
					continue;
				}
				std::cout << "," << pCommas;
				i++;
			}
			std::cout << std::endl;
		}

	std:cout << "================================================================================" << std::endl;
	}
};

// database manager for Recipe
// performs file I/O operations, db items printing
class RecipeDB : public DataBase<std::string, Recipe> {
private:

public:
	// CTOR
	RecipeDB() {
		// msg
		// std::cout << "[디버그] recipe DB 생성" << std::endl;
		// Load File
		std::vector<std::map<std::string, std::string>*> parsedData = CSVParser::instance().read("IIKHRecipeDB.csv");

		for (auto myMap : parsedData) {
			// Construct Recipe Name from csv
			std::string recipeName = myMap->find("name")->second;

			// Construct Plan from csv
			Recipe* recipePtr = new Recipe(
				// Recipe name
				std::string(myMap->find("name")->second),
				// Recipe descrition
				std::string(myMap->find("description")->second),
				// Recipe time
				atoi((myMap->find("time")->second).c_str()),
				// Recipe ingredients
				CSVParser::instance().split(myMap->find("ingredients")->second,'$',-1)
			);
			// insert to DB
			this->_insert(recipeName, *recipePtr);
		}
	};
	// DTOR
	~RecipeDB() {};

	// select item by given date and print 
	void _show(std::string key) {
		this->_select(key).print();
	}
	// show all items in DB
	void _showAll() {
		for (std::pair<std::string, Recipe> s : db)
			s.second.print();
	}
	// save to local
	void _save() {
		CSVParser::instance().write("IIKHRecipeDB.csv", _setRecipeDBData());
	};

	// used for saving Recipe Data
	std::vector<std::map<std::string, std::string>*> _setRecipeDBData() {
		// variable
		std::vector<std::map<std::string, std::string>*> *savedData = new std::vector<std::map<std::string, std::string>*>();
		int id = 0;
		int index = 0;

		// hard code keys 
		std::vector<std::string> keys;
		keys.push_back(std::string("index")); //0
		keys.push_back(std::string("name")); //1
		keys.push_back(std::string("description")); //2
		keys.push_back(std::string("time")); //3
		keys.push_back(std::string("ingredients")); //4

		for (std::pair<std::string, Recipe> dbItemPair : db)
		{
			// get dbItem
			Recipe targetRecipe = dbItemPair.second;

			// one item
			std::map<std::string, std::string>* item = new std::map<std::string, std::string>();

			item->insert(make_pair(keys[0], std::to_string(id)));
			item->insert(make_pair(keys[1], targetRecipe.getName()));
			item->insert(make_pair(keys[2], targetRecipe.getDescription()));
			item->insert(make_pair(keys[3], std::to_string(targetRecipe.getTime())));
			item->insert(make_pair(keys[4], targetRecipe.getIngredientsIntoString()));

			// push to vector
			savedData->push_back(item);
			// inc id
			id++;
		}

		// In case of Empty case (write함수에서 key를 설정하는 방식으로 인해 빈 맵이 있어야함)
		if (savedData->size() == 0) {
			std::map<std::string, std::string>* item = new std::map<std::string, std::string>();
			bool isFirst = true;
			for (auto myKey : keys) {
				if (isFirst) {
					continue;
					isFirst = false;
				}
				item->insert(make_pair(myKey, std::string("")));
			}
			item->insert(make_pair(keys[0], std::to_string(id)));
			// push to vector
			savedData->push_back(item);
		}

		return *savedData;
	}
};