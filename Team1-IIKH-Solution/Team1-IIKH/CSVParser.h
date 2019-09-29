#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

// stores path, delimiter
// performs Writing, Reading Files to specified path
class CSVParser
{
private:
	// Empty CTOR
	CSVParser() { };
	
	// used in case of fixed path
	std::string rootPath = "";
	// delimiter
	char delimiter = ',';
	// convert map type data to string to save it as csv
	string convertToString(map<string, string>);
	string convertToString(vector<string>, char);
public:
	// singleton
	static CSVParser& instance() {
		// instance var. for sigleton
		static CSVParser* instancePtr = new CSVParser();
		
		return *instancePtr;
	}
	// split string(tokenize)
	std::vector<std::string> split(std::string, char, int);
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
		std::cout << "Failed to open file. Check if " << filename << "exists" << std::endl;
	}

	return *parsedData;
}

// write file
void CSVParser::write(std::string filename, std::vector<std::map<std::string, std::string>*> data) {
	//get keys and convert to string
	map<string, string> m_dataPiece = *data[0];
	vector<string> v_keys;

	for (map<string, string>::iterator it = m_dataPiece.begin(); it != m_dataPiece.end(); ++it)
	{
		v_keys.push_back(it->first);
	}

	//convert data to string
	string buffer(convertToString(v_keys, delimiter));		//push converted key string to buffer 

	for (auto item : data)
	{
		m_dataPiece = *item;

		buffer.append(convertToString(m_dataPiece));

		data.erase(data.begin());
	}

	std::ofstream writer(filename);
	writer << buffer;
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

string CSVParser::convertToString(map<string, string> data)
{
	vector<string> v_values;

	for (map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
	{
		v_values.push_back(it->second);
	}

	return convertToString(v_values, delimiter);
}

string CSVParser::convertToString(vector<string> data, char delimiter)
{
	string buffer;
	string delString(1, delimiter);
	for (int i = 0; i < data.size(); i++)
	{
		buffer.append(data[i]);
		if (i + 1 != data.size())
			buffer.append(delString);
	}
	buffer.append("\n");
	return buffer;
}

// ���� ����
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