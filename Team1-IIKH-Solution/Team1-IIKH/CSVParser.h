#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

// stores path, delimiter
// performs Writing, Reading Files to specified path
class CSVParser
{
private:
	// used in case of fixed path
	std::string rootPath = "";		
	// delimiter
	char delimiter = ',';
	// split string(tokenize)
	std::vector<std::string> split(std::string, char, int);
public:
	// read text of given filename
	std::vector<std::map<std::string, std::string>*> read(std::string);
	// write text to given path
	void write(std::string, std::vector<std::map<std::string, std::string>*>);
};

// CSVParser Class' Read Function
// reads text of given filename and returns
std::vector<std::map<std::string, std::string>*> CSVParser::read(std::string filename) {
	std::ifstream reader(filename);

	std::vector<std::map<std::string, std::string>*> *parsedData = new std::vector<std::map<std::string, std::string>*>();

	// check if c stream is opened
	if (reader.is_open())
	{
		std::string line;
		getline(reader, line);
		std::vector<std::string> keys = split(line, delimiter, -1);

		int index = 0;

		// read text by line 
		while (getline(reader, line))
		{
			std::map<std::string, std::string> *temp = new std::map<std::string, std::string>();

			std::vector<std::string> values = split(line, delimiter, keys.size());

			for (int i = 0; i < keys.size(); i++)
			{
				temp->insert(make_pair(keys[i], values[i]));
			}

			parsedData->push_back(temp);
		}
	}
	else 
	{
		std::cout << "Failed to open file. Check if "<< filename << "exists" << std::endl;
	}

	return *parsedData;
}

// write file
void CSVParser::write(std::string filename, std::vector<std::map<std::string, std::string>*> data) {
	std::ofstream writer(filename);
}

// split string by delimiter
std::vector<std::string> CSVParser::split(std::string str, char delimiter, int size) {
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

// 실행 예시
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