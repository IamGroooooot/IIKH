#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

class CSVParser
{
private:
	std::string rootPath = "";		//고정된 경로일 경우
	char delimitor = ',';
	std::vector<std::string> Split(std::string, char, int);
public:
	std::vector<std::map<std::string, std::string>*> Read(std::string);
	void Write(std::string, std::vector<std::map<std::string, std::string>*>);
};

/*
void main()
{
	CSVParser parser;
	std::vector<std::map<std::string, std::string>*> parsedData = parser.Read("IIKHRecipe.csv");

	for (int i = 0; i < parsedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = parsedData[i];
		for (auto it = temp->cbegin(); it != temp->cend(); ++it)
		{
			std::cout << it->second << "\n";
		}
	}
}*/

std::vector<std::map<std::string, std::string>*> CSVParser::Read(std::string filename) {
	std::ifstream reader(filename);

	std::vector<std::map<std::string, std::string>*> *parsedData = new std::vector<std::map<std::string, std::string>*>();

	if (reader.is_open())
	{
		std::string line;
		getline(reader, line);
		std::vector<std::string> keys = Split(line, delimitor, -1);

		int index = 0;

		while (getline(reader, line))
		{
			std::map<std::string, std::string> *temp = new std::map<std::string, std::string>();

			std::vector<std::string> values = Split(line, delimitor, keys.size());

			for (int i = 0; i < keys.size(); i++)
			{
				temp->insert(make_pair(keys[i], values[i]));
			}

			parsedData->push_back(temp);
		}
	}
	return *parsedData;
}

void CSVParser::Write(std::string filename, std::vector<std::map<std::string, std::string>*> data) {
	std::ofstream writer(filename);
}

std::vector<std::string> CSVParser::Split(std::string str, char delimiter, int size) {
	std::vector<std::string> internal;
	std::stringstream ss(str);
	std::string temp;

	int i = 1;

	while (getline(ss, temp, delimiter)) {
		if (temp.empty()) internal.push_back("");
		else internal.push_back(temp);
	}

	if (size > -1)
		if (i != size)
			internal.push_back("");

	return internal;
}