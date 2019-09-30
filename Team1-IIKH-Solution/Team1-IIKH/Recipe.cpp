#include "Recipe.h"
#include "CSVParser.h"

#include <vector>

RecipeDB::RecipeDB() {
	enum { NAME = 0, DESCRIPTION, TIME, INGREDIENT };
	auto DB = CSVParser::getInstance().read(std::string("RecipeDB.csv"));
	for (auto record : DB) {
		if (record.size() != 4) throw CSVParserException(0, "");
		this->_insert(record[NAME], Recipe(record[NAME], record[DESCRIPTION], std::atoi(record[TIME].c_str()), split(record[INGREDIENT])));
	}
}

void RecipeDB::_save() {
	std::string ingre = {}, line = {};
	std::vector<std::string> res;
	for (auto record : db) {
		ingre += '"';
		for (auto var : record.second.getIngredients()) {
			ingre += var;
			ingre += ",";
		}
		ingre[ingre.size() - 1] = '"';
		line = record.second.getName() + ',';
		line += record.second.getDescription() + ',';
		line += std::to_string(record.second.getTime()) + ',';
		line += ingre;
		res.push_back(line);
		line.erase();
		ingre.erase();
	}
	CSVParser::getInstance().write(std::string("RecipeDB.csv"), res);
}