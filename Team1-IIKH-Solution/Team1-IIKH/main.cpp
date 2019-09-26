#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"

int main() {
	PlanDB plan;
	try {
		plan.Insert(Date(2019, 8, 30), Plan(std::string("1"), { 
			Meal({ std::string("5"), std::string("2") }),
			Meal({ std::string("6"), std::string("3") }),
			Meal({ std::string("7"), std::string("4") }) 
		}));
		plan.Insert(Date(2019, 8, 30), Plan(std::string("q"), { 
			Meal({ std::string("a"), std::string("f") }),
			Meal({ std::string("b"), std::string("w") }),
			Meal({ std::string("c"), std::string("e") }) 
		}));
		plan.Insert(Date(2019, 8, 29), Plan(std::string("x"), { 
			Meal({ std::string("z"), std::string("l") }),
			Meal({ std::string("df"), std::string("m") }),
			Meal({ std::string("g"), std::string("c") }) 
		}));
		plan.Insert(Date(2019, 8, 31), Plan(std::string("j"), { 
			Meal({ std::string("qw") }),
			Meal({ std::string("ascx"), std::string("h") }),
			Meal({ std::string("cx"), std::string("q") }) 
		}));
		plan.Select(Date(2019, 7, 31));
		plan.ShowAll();
	}
	catch (DBException e) {
		e.resolve();
	}
	return 0;
}