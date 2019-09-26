#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"

int main() {
	PlanDB plan;
	CSVParser parser;


	try {
		plan.Insert(Date(2019, 8, 28), Plan(std::string("��� "), {
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		plan.Insert(Date(2019, 8, 30), Plan(std::string("���3"), {
			Meal({ std::string("��"), std::string("��� �Ķ���") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		plan.Insert(Date(2019, 8, 29), Plan(std::string("���2"), {
			Meal({ std::string("��"), std::string("��") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		plan.Insert(Date(2019, 8, 31), Plan(std::string("���4"), {
			Meal({ std::string("������ġ") }),
			Meal({ std::string("��"), std::string("��ġ") }),
			Meal({ std::string("��"), std::string("��ġ") })
			}));
		plan.Select(Date(2019, 8, 31));
		plan.ShowAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	
	std::vector<std::map<std::string, std::string>*> parsedData = parser.Read("IIKHRecipe.csv");

	for (int i = 0; i < parsedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = parsedData[i];
		for (auto it = temp->cbegin(); it != temp->cend(); ++it)
		{
			std::cout << it->second << "\n";
		}
	}


	return 0;
}