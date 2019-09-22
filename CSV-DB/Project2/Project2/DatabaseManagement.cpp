#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>

class RecipeDatabase {
private:
	std::string path;
	std::vector<RecipeData> recipes;
public:
	void LoadDB();
	void SaveDB();
};

class RecipeData {
private:
	std::string name;
	std::string description;
	int time;
	std::vector<std::string> ingredients;
public:
	RecipeData(std::map<std::string, std::string>);

	bool FindIngredient(std::string);

	std::string GetName();
	std::string GetDescription();
	int GetTime();
	std::vector<std::string> GetIngredients();
};

//프로그램 상에서 나열되고 필터링되는 레시피 리스트
class RecipeList {

};

void RecipeDatabase::LoadDB() {
	
}

void RecipeDatabase::SaveDB() {

}