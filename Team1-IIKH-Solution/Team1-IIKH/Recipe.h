#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "Database.h"

class Recipe {
private:
	std::string name;
	std::string descript;
	std::set<std::string> ingredient;
	int time;

public:
	Recipe(std::string & n, std::string & d, int t, std::vector<std::string> i) :
		name(n), descript(d), time(t), ingredient() {
		for (std::string s : i)
			ingredient.insert(s);
	};
	const std::string & getName() { return name; }
	const std::string & getDescription() { return descript; }
	const std::set<std::string> & getIngredients() { return ingredient; }
	int getTime() { return time; }

	void setName(std::string & n) { name = n; }
	void setDescription(std::string & d) { descript = d; }
	void setTime(int t) { time = t; }

	bool addIngredient(std::string & n) { return ingredient.insert(n).second; }
	bool removeIndgredient(std::string & n) { return ingredient.erase(n) == 1; }
	bool searchIndgredient(std::string & n) { return ingredient.find(n) != ingredient.end(); }

	void print() {
		std::cout << "이름 : " << name << std::endl;
		std::cout << "재료 : ";
		for (std::string s : ingredient)
			std::cout << s << ' ';
		std::cout << std::endl;
		std::cout << "시간 : " << time << std::endl;
		std::cout << "요리법 : " << descript << std::endl;
	}
};

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