#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class RecipeDatabase {
private:
	std::string path;
	std::vector<RecipeData> recipes;
public:
	void LoadDB();
	void SaveDB();		//레시피 데이터들을 저장해주는 부분

	RecipeData GetData(int id);
	void AddData(RecipeData);
};

class RecipeData {
private:
	int id;
	std::string name;
	std::string description;
	int time;
	std::vector<std::string> ingredients;
public:
	RecipeData(std::map<std::string, std::string>);

	//필요한가?
	bool EditData(std::map<std::string, std::string>);

	bool FindIngredient(std::string);

	std::string GetName();
	std::string GetDescription();
	int GetTime();
	std::vector<std::string> GetIngredients();
};

class CSVParser {
private:

public:
	std::map<std::string, std::string> Read(std::string);
};

//프로그램 상에서 나열되고 필터링되는 레시피 리스트
class RecipeList {

};

void RecipeDatabase::LoadDB() {
	
}

void RecipeDatabase::SaveDB() {

}

std::map<std::string, std::string> Read(std::string path) {
	
}

void main()
{
	std::ofstream temp("test.txt");
}