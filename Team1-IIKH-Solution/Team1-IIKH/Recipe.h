#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"

// stores recipe's name, description, ingredients, time
// and performs action related to recipe and it's member.
class Recipe {
private:
	// Recipe's Name
	std::string name;
	// Recipe's Description
	std::string descript;
	// Recipe's Ingredients: it is set of ingredient(we use "string" for ingredient)
	std::set<std::string> ingredient;
	// Recipe's Expected Time it takes to cook. 
	int time;

public:
	// CTOR: name, description, time, ingredient will be initialized
	Recipe(std::string & n, std::string & d, int t, std::vector<std::string> i) :
		name(n), descript(d), time(t), ingredient() {
		// insert all ingredients to ingredient set
		for (std::string s : i)
			ingredient.insert(s);
	};

	// returns Recipe name
	const std::string & getName() { return name; }
	// returns Recipe description
	const std::string & getDescription() { return descript; }
	// returns Recipe ingredient
	const std::set<std::string> & getIngredients() { return ingredient; }
	// returns Recipe time
	int getTime() { return time; }

	// sets Recipe name
	void setName(std::string & n) { name = n; }
	// sets Recipe description
	void setDescription(std::string & d) { descript = d; }
	// sets Recipe time
	void setTime(int t) { time = t; }

	// insert Recipe ingredient to ingredient set. and returns second stored value
	bool addIngredient(std::string & n) { return ingredient.insert(n).second; }
	// remove Recipe ingredient to ingredient set. and returns second stored value
	bool removeIngredient(std::string & n) { return ingredient.erase(n) == 1; }
	// find if there is ingredient
	bool searchIngredient(std::string & n) { return ingredient.find(n) != ingredient.end(); }

	// print Recipe datas
	void print() {
		std::cout << "Recipe Name : " << name << std::endl;
		std::cout << "Ingredient : ";
		for (std::string s : ingredient)
			std::cout << s << ' ';
		std::cout << std::endl;
		std::cout << "Expected Time : " << time << std::endl;
		std::cout << "Direction : " << descript << std::endl << std::endl;
	}
};

// database manager for Recipe
// performs file I/O operations, db items printing
class RecipeDB : public DataBase<std::string, Recipe> {
private:

public:
	RecipeDB() {};
	~RecipeDB() {};
	void ShowAll() {
		for (std::pair<std::string, Recipe> s : db)
			s.second.print();
	}
	void Show(std::string key) {
		this->Select(key).print();
	}
	void Save() {};
};