#pragma once
#include <set>
#include <string>
#include <iostream>

#include "Database.h"
#include "Recipe.h"

// stores three meals
class Meal {
private:
	// set, sorts recipes in alphabetical order
	std::set<std::string> Recipes;

public:
	// CTOR: saves Recipe vector[argument] into Recipes set[class member]
	Meal(std::vector<std::string> r) {
		for (std::string s : r)
			Recipes.insert(s);
	}

	// return current recipes
	auto & getRecipes() { return Recipes; }
	// add new recipe into Recipes set[class member]
	void addRecipes(std::string & n) {Recipes.insert(n);}
	// if the recipe target[argument] is in the recipes, return 1, else return 0
	bool searchRecipes(std::string & target) {return Recipes.find(target) != Recipes.end();}
	// delete target recipe from Recipes set[class member]
	void deleteRecipes(std::string & target) {Recipes.erase(target); }

	// print all recipes
	void print() {
		for (std::string recipe : Recipes)
			std::cout << recipe << ' ';
		//std::cout<<std::endl;
	}
};


class Date {
private:
	// variables for Date
	int year, month, day;
	// save date in format("%04d%02d%02d")
	std::string dateString;

public:
	// CTOR
	Date(int y, int m, int d) :
		year(y), month(m), day(d) {
		char temp[9];
		sprintf_s(temp, 9, "%04d%02d%02d", year, month, day);
		dateString.append(temp);
	};

	// date ordering standard
	friend bool operator<(const Date & first, const Date & second) {
		if (first.year < second.year) return true;
		if (first.year > second.year) return false;
		if (first.month < second.month) return true;
		if (first.month > second.month) return false;
		if (first.day < second.day) return true;
		return false;
	}

	// return dateString into .c format string
	const char * c_str() { return dateString.c_str(); }
};

// stores Meals(Breakfast, Lunch, Dinner) which is daily meal plan
class Plan {
private:
	// Plan name
	std::string name;
	// Plan has three meal instance
	Meal Breakfast, Lunch, Dinner;

public:
	// CTOR
	Plan(std::string && n, std::vector<Meal> m) :
		name(n), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]) {};
	
	/* GET */
	// get Plan name
	const std::string & getName() const { return name; }
	// get Breakfast Meal
	const Meal & getBreakfast() const { return Breakfast; }
	// get Lunch Meal
	const Meal & getLunch() const { return Lunch; }
	// get Dinner Meal
	const Meal & getDinner() const { return Dinner; }

	/* SET */
	// set Plan name
	void setName(std::string & _name) { name = _name; }
	// set Breakfast Meal
	void setBreakfast(Meal & b) { Breakfast = b; }
	// set Lunch Meal
	void setLunch(Meal & l) { Lunch = l; }
	// set Dinner Meal
	void setDinner(Meal & d) { Dinner = d; }

	// prints all meal plan
	void print() {
		std::cout << "Plan Name : " << name << std::endl;
		std::cout << "Breakfast : "; Breakfast.print(); std::cout << std::endl;
		std::cout << "Lunch : "; Lunch.print(); std::cout << std::endl;
		std::cout << "Dinner : "; Dinner.print(); std::cout << std::endl << std::endl;
	}
};

// database manager for Plan
// performs file I/O operations, db items printing
class PlanDB : public DataBase<Date, Plan> {
private:

public:
	// CTOR
	PlanDB() {};
	// DTOR
	~PlanDB() {};

	// select item by given date and print 
	void _show(Date key) {
		this->_select(key).print();
	}
	// show all items in DB
	void _showAll() {
		for (auto p : db)
			p.second.print();
	}
	// save into local
	void _save() {};
};