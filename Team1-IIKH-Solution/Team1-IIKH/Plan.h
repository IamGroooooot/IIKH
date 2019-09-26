#pragma once
#include <set>
#include <string>
#include <iostream>

#include "Database.h"
#include "Recipe.h"

//# recipes in 1 meal
class Meal {

private:

	//Sort recipes in alphabetical order
	std::set<std::string> Recipes;

public:

	//Meal constructor
	Meal(std::vector<std::string> r) {
		for (std::string s : r)
			Recipes.insert(s);
	}

	//Return current recipes
	auto & getRecipes() { return Recipes; }

	void addRecipes(std::string & n) {Recipes.insert(n);}

	//If the recipe you're looking for is in the recipes, return 1 else return 0
	bool searchRecipes(std::string & n) {return Recipes.find(n) != Recipes.end();}


	void deleteRecipes(std::string & n) {Recipes.erase(n); }


	void print() {
		for (std::string s : Recipes)
			std::cout << s << ' ';
		//std::cout<<std::endl;
	}
};

class Date {
private:

	int year, month, day;
	std::string name;

public:

	
	Date(int y, int m, int d) :
		year(y), month(m), day(d) {
		char temp[9];
		sprintf_s(temp, 9, "%04d%02d%02d", year, month, day);
		name.append(temp);
	};

	//Date ordering standard
	friend bool operator<(const Date & first, const Date & second) {
		if (first.year < second.year) return true;
		if (first.year > second.year) return false;
		if (first.month < second.month) return true;
		if (first.month > second.month) return false;
		if (first.day < second.day) return true;
		return false;
	}


	const char * c_str() { return name.c_str(); }
};

//3 meals in 1 plan
class Plan {

private:

	std::string name;
	Meal Breakfast, Lunch, Dinner;

public:

	Plan(std::string && n, std::vector<Meal> m) :
		name(n), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]) {};
	
	const std::string & getName() { return name; }

	//Get each meal
	const Meal & getBreakfast() { return Breakfast; }
	const Meal & getLunch() { return Lunch; }
	const Meal & getDinner() { return Dinner; }

	void setName(std::string & n) { name = n; }

	//Set each meal
	void setBreakfast(Meal & b) { Breakfast = b; }
	void setLunch(Meal & l) { Lunch = l; }
	void setDinner(Meal & d) { Dinner = d; }

	void print() {
		std::cout << "Plan Name : " << name << std::endl;
		std::cout << "Breakfast : "; Breakfast.print(); std::cout << std::endl;
		std::cout << "Lunch : "; Lunch.print(); std::cout << std::endl;
		std::cout << "Dinner : "; Dinner.print(); std::cout << std::endl << std::endl;
	}
};

class PlanDB : public DataBase<Date, Plan> {

private:

public:

	PlanDB() {};
	~PlanDB() {};


	void Show(Date key) {
		this->Select(key).print();
	}

	
	void ShowAll() {
		for (auto p : db)
			p.second.print();
	}
	void Save() {};
};