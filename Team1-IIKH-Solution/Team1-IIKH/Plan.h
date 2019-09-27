#pragma once
#include <set>
#include <string>
#include <iostream>

#include "Database.h"
#include "Recipe.h"

// stores a lot of RecipeNames
class Meal {
private:
	// set, sorts recipes in alphabetical order
	std::set<std::string> recipeNames;
	std::string recipeString;

public:
	// Empty CTOR
	Meal() {
		
	}

	// CTOR: saves Recipe vector[argument] into RecipeNames set[class member]
	Meal(std::vector<std::string> r) {
		for (std::string s : r)
			recipeNames.insert(s);
	}

	// return current recipes
	auto & getRecipes() { return recipeNames; }
	// add new recipe into Recipes set[class member]
	void addRecipes(std::string & n) { recipeNames.insert(n);}
	// if the recipe target[argument] is in the recipes, return 1, else return 0
	bool searchRecipes(std::string & target) {return recipeNames.find(target) != recipeNames.end();}
	// delete target recipe from Recipes set[class member]
	void deleteRecipes(std::string & target) { recipeNames.erase(target); }

	std::string getRecipeNamesIntoString() {
		int maxCnt = 0;
		for (auto _recipe : recipeNames) {
			recipeString.append(_recipe);
			recipeString.append("$");

			maxCnt++;
			if (maxCnt == 4) {
				break;
			}
		}

		return recipeString;
	}

	// print all recipes
	void print() {
		for (std::string recipe : recipeNames)
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
	Date(char temp[9])
	{
		sscanf_s(temp, "%04d%02d%02d", &year, &month, &day);
	};
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

	std::string getDateString() {
		return dateString;
	}

	// return dateString into .c format string
	const char * c_str() { return dateString.c_str(); }
};

// stores Meals(Breakfast, Lunch, Dinner) which is daily meal plan
class Plan {
private:
	// Plan name
	std::string name;
	// Date
	Date date;

	// Plan has three meal instance
	Meal Breakfast, Lunch, Dinner;

public:
	// CTOR name date mealVector
	Plan(std::string && n, Date date, std::vector<Meal> m ) :
		name(n), Breakfast(m[0]), Lunch(m[1]), Dinner(m[2]), date(date) {};
	
	/* GET */
	// get Plan name
	const std::string & getName() const { return name; }
	// get Plan date
	Date getDate() const { return date; }
	// get Breakfast Meal
	Meal getBreakfast() const { return Breakfast; }
	// get Lunch Meal
	Meal getLunch() const { return Lunch; }
	// get Dinner Meal
	Meal getDinner() const { return Dinner; }

	/* SET */
	// set Plan name
	void setName(std::string & _name) { name = _name; }
	// set Plan date
	void setDate(char dateString[9]) {
		date = *(new Date(dateString));
	}
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

// database manager for Plan(name + 3 meal)
// performs file I/O operations, db items printing
class PlanDB : public DataBase<Date, Plan> {
private:
	  
public:
	// CTOR
	PlanDB() {
		// msg
		std::cout << "[디버그] Plan DB 생성" << std::endl;
		// Load File
		std::vector<std::map<std::string, std::string>*> parsedData = CSVParser::instance().read("IIKHPlanDB.csv");
		for (auto myMap : parsedData) {
			// Construct Date from csv
			Date* datePtr = new Date(    strdup(  ( myMap->find("date")->second.c_str() )  )    );

			// Construct Plan from csv
			Plan* planPtr = new Plan( 
				// plan name
				std::string(myMap->find("name")->second),
				*datePtr, 
				{
					//아침
					Meal( CSVParser::instance().split(  myMap->find("breakfast")->second  , '$', -1  ) ),
					//점심
					Meal( CSVParser::instance().split(  myMap->find("lunch")->second  , '$', -1  ) ),
					//저녁
					Meal( CSVParser::instance().split(  myMap->find("dinner")->second  , '$', -1) )
				}
			);
			// insert to DB
			this->_insert(*datePtr,*planPtr);
		}
	};
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


	// used for saving Plan Data
	std::vector<std::map<std::string, std::string>*> _setPlanDBData() {
		// variable
		std::vector<std::map<std::string, std::string>*> *saveData = new std::vector<std::map<std::string, std::string>*>();
		int id = 0;
		int index = 0;

		// hard code keys 
		std::vector<std::string> keys;
		keys.push_back(std::string("index")); //0
		keys.push_back(std::string("name")); //1
		keys.push_back(std::string("date")); //2
		keys.push_back(std::string("breakfast")); //3
		keys.push_back(std::string("lunch")); //4
		keys.push_back(std::string("dinner")); //5

		for (std::pair<Date, Plan> dbItemPair : db)
		{
			// get dbItem
			Plan targetPlan = dbItemPair.second;

			// one item
			std::map<std::string, std::string>* item = new std::map<std::string, std::string>();

			item->insert(make_pair(keys[0], std::to_string(id)));
			item->insert(make_pair(keys[1], targetPlan.getName()));
			item->insert(make_pair(keys[2], targetPlan.getDate().getDateString()));
			item->insert(make_pair(keys[3], targetPlan.getBreakfast().getRecipeNamesIntoString()));
			item->insert(make_pair(keys[4], targetPlan.getLunch().getRecipeNamesIntoString()));
			item->insert(make_pair(keys[5], targetPlan.getDinner().getRecipeNamesIntoString()));


			// push to vector
			saveData->push_back(item);
			// inc id
			id++;
		}

		return *saveData;
	}
};