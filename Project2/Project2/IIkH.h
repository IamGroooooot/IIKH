#pragma once
#include <iostream>
#include <vector>

class Greeter {
private:
	PlanManager & proc;
	DataBaseManager & DB;
public:
	Greeter(PlanManager & p, DataBaseManager & db) : proc(p), DB(db) {};
	void Init();
	void Menu();
	void SubMenu(int i);
};

class PlanManager {
private:
	struct Date {
		DataBaseManager::Meal meal;
	};
	std::vector<Date> dates;

public:
	PlanManager() {};
};

class DataBaseManager {
private:
	struct Meal {

	};

	struct Recipe {

	};

	std::vector<Meal> meals;
	std::vector<Recipe> recipes;

public:
	friend PlanManager;
};