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
	void SaveDB();		//������ �����͵��� �������ִ� �κ�

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

	//�ʿ��Ѱ�?
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

//���α׷� �󿡼� �����ǰ� ���͸��Ǵ� ������ ����Ʈ
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