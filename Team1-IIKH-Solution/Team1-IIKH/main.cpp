#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"

int main() {
	PlanDB plan;
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
	return 0;
}