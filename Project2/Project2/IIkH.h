#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>

class Greeter {
private:
	PlanManager & proc;
	DataBaseManager & DB;
public:
	Greeter(PlanManager & p, DataBaseManager & db) :
		proc(p), DB(db) {};
	void Init();
	void Menu();
	void SubMenu(int i);
};

class PlanManager {
private:
	class Date {
	private:
		enum { BREAKFAST = 0, LAUNCH, DINNER };
		int year, month, day;
		DataBaseManager::Meal meals[3];

	public:
		Date(int y, int m, int d) :
			year(y), month(m), day(d) {
		};
		void DisplayAndEdit();
		void BuildGroceryList( DataBaseManager::Meal * m);
		friend bool operator<(const Date& first, const Date& second) {
			if (first.year < second.year) return true;
			if (first.year > second.year) return false;
			if (first.month < second.month) return true;
			if (first.month > second.month) return false;
			if (first.day < second.day) return true;
			return false;
		}
	};
	std::set<Date> dates;

public:
	PlanManager() {};

};

class DataBaseManager {
private:
	class Recipe {
	private:
		std::string name;
		std::string description;
	public:

	};

	class Meal {
	private:
		std::string name;
		std::vector<int> rec;
	public:
		Meal(std::string&& n = std::string("")) :
			name(n), rec(5) {};
		void addRecipe(Recipe& r);
		friend bool operator<(const Meal& first, const Meal& second) {
			return first.name < second.name;
		}
	};

	std::set<Meal> meals;
	std::vector<Recipe> recipes;

public:
	friend PlanManager;

};