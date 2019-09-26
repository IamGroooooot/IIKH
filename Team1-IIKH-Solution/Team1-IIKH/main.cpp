#include <iostream>
#include <string>
#include <vector>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"

int main() {
	PlanDB plan;
	try {
		plan.Insert(Date(2019, 8, 28), Plan(std::string("Æò¹ü "), {
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan.Insert(Date(2019, 8, 30), Plan(std::string("Æò¹ü3"), {
			Meal({ std::string("¹ä"), std::string("°è¶õ ÈÄ¶óÀÌ") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan.Insert(Date(2019, 8, 29), Plan(std::string("Æò¹ü2"), {
			Meal({ std::string("¹ä"), std::string("±¹") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan.Insert(Date(2019, 8, 31), Plan(std::string("Æò¹ü4"), {
			Meal({ std::string("»÷µåÀ§Ä¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
			Meal({ std::string("¹ä"), std::string("±èÄ¡") })
			}));
		plan.Select(Date(2019, 8, 31));
		plan.ShowAll();
	}
	catch (DBException e) {
		e.resolve();
	}
	return 0;
}