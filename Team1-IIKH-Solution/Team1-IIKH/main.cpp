#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <limits>

#include "Database.h"
#include "Recipe.h"
#include "Plan.h"
#include "CSVParser.h"

void printMenu(std::vector<std::string> &menu); //Print menu in console
void addMenu(std::vector<std::string> &menu, std::string instruction); //Add instruction to menu (Order matters)
void selectMenu(std::vector<std::string> &menu, PlanDB &planDB, RecipeDB &recipeDB); //Menu selection, corresponding function executed
void searchRecipe(RecipeDB& recipeDB);
void addRecipe(RecipeDB& recipeDB);
void addPlan(PlanDB& planDB);
Meal addMeal(std::string mealName);

int main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	PlanDB planDB;
	RecipeDB recipeDB;
	//CSVParser parser;


    std::vector<std::string> menu;

    //Add menu here
    addMenu(menu,"SEARCH RECIPE");
    addMenu(menu,"ADD RECIPE");
    addMenu(menu,"VIEW RECIPE");
    addMenu(menu,"ADD PLAN");
    addMenu(menu,"VIEW PLAN");
    addMenu(menu,"QUIT");

	try {
		Recipe* recipeElement1 = new Recipe(std::string("Á¶¤Ç¤©¶ó°Ô ¸ÀÀÖ´Â ·¹½ÃÇÇ 1"), std::string("°Ì³ª ¸ÀÀÖ°Ô ¸¸µç´Ù."), 100, {std::string("Àç·á1"), std::string("Àç·á2") });
		recipeDB._insert(std::string("insert 1"), *recipeElement1);
		Recipe* recipeElement2 = new Recipe(std::string("Á¹¶ó¤Ó¸À¾ø´Â ·¹½ÃÇÇ2"), std::string("°Ì³ª ¸À¾ø°Ô ¸¸µç´Ù."), 10, { std::string("Àç·á1123"), std::string("Àç·á2123") });
		recipeDB._insert(std::string("insert 2"), *recipeElement2);
		recipeDB._showAll();
	}
	catch (DBException e) {
		e.resolve();
	}

	try {
			planDB._insert(Date(2019, 8, 28), Plan(std::string("Æò¹ü "), Date(2019, 8, 28), {
				Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") })
				}));
			planDB._insert(Date(2019, 8, 30), Plan(std::string("Æò¹ü3"), Date(2019, 8, 30), {
				Meal({ std::string("¹ä"), std::string("°è¶õ ÈÄ¶óÀÌ") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") })
				}));
			planDB._insert(Date(2019, 8, 29), Plan(std::string("Æò¹ü2"), Date(2019, 8, 29), {
				Meal({ std::string("¹ä"), std::string("±¹") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") })
				}));
			planDB._insert(Date(2019, 8, 31), Plan(std::string("Æò¹ü4"), Date(2019, 8, 31), {
				Meal({ std::string("»÷µåÀ§Ä¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") }),
				Meal({ std::string("¹ä"), std::string("±èÄ¡") })
				}));
			planDB._select(Date(2019, 8, 31));
			//plan._showAll();
		}
		catch (DBException e) {
			e.resolve();
		}



	cout << "------Print My Meal Plans------" << endl;
	planDB._showAll();
	cout << "------Print My Recipes------" << endl;
	recipeDB._showAll();

    while(true)
    {
        printMenu(menu);
        selectMenu(menu,planDB,recipeDB);
    }


	

	std::cout << "----------------File ºÒ·¯¿À±â Test----------------" << std::endl;
	
	std::vector<std::map<std::string, std::string>*> parsedData = CSVParser::instance().read("IIKHRecipe.csv");

	for (int i = 0; i < parsedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = parsedData[i];
		for (auto it = temp->cbegin(); it != temp->cend(); ++it)
		{
			std::cout << it->first << " | " << it->second << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << "----------------¼¼ÀÌºêµ¥ÀÌÅ¸ »ý¼º Test----------------" << std::endl;

	std::vector<std::map<std::string, std::string>*> savedData = recipeDB._setRecipeDBData();
	for (int i = 0; i < savedData.size(); i++)
	{
		std::map<std::string, std::string>* temp = savedData[i];
		for (auto item = temp->cbegin(); item != temp->cend(); ++item)
		{
			std::cout << item->first<<" | "<< item->second << std::endl;
			
		}
		std::cout << std::endl;
	}
	return 0;

	// std::vector<std::map<std::string, std::string>*> parsedData = parser.Read("IIKHRecipe.csv");

	// for (int i = 0; i < parsedData.size(); i++)
	// {
	// 	std::map<std::string, std::string>* temp = parsedData[i];
	// 	for (auto it = temp->cbegin(); it != temp->cend(); ++it)
	// 	{
	// 		std::cout << it->second << "\n";
	// 	}
	// }


	// return 0;
}

void addMenu(std::vector<std::string> &menu, std::string instruction){menu.push_back(instruction);}
void printMenu(std::vector<std::string> &menu)
{
    std::cout<<"IIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nIIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH"<<std::endl;
    std::cout<<"Here's Menu"<<std::endl;
    int size = menu.size();
    for(int i = 1;i<=size;i++)std::cout<<"Enter ["<<i<<"] to <"<<menu[i-1]<<">"<<std::endl;
}
void selectMenu(std::vector<std::string> &menu, PlanDB &planDB, RecipeDB &recipeDB)
{
        int selectedNum;std::cin>>selectedNum;
        std::cout<<"You've selected ["<<selectedNum<<"] ";
        switch (selectedNum)
        {
            case 1:
            {
				std::cout<<"to search recipe"<<std::endl;
				searchRecipe(recipeDB);
                break;
            }
            case 2:
            {
				std::cout<<"to add recipe"<<std::endl;
				addRecipe(recipeDB);
                break;
            }
            case 3:
            {
				std::cout<<"to view recipe"<<std::endl;
				recipeDB._showAll();

                break;
            }
            case 4:
            {
				std::cout<<"to add plan"<<std::endl;
				addPlan(planDB);
                break;
            }
            case 5:
            {
				std::cout<<"to view plan"<<std::endl;
                planDB._showAll();
                break;
            }
            case 6:
            {
                std::cout<<"to QUIT..."<<std::endl;
                exit(0);
                break;
            }
            default:
            {
                std::cout<<"PLEASE ENTER NUMBER FROM 1 ~ "<<menu.size()<<std::endl;
                break;
            }
        }
}
void searchRecipe(RecipeDB& recipeDB)
{
    std::cout<<"Search : "<<std::flush;
	std::cin.ignore();
	std::string searchM;std::getline(std::cin,searchM);			
	Recipe recipe = recipeDB._select(searchM);
	recipe.print();
}
void addRecipe(RecipeDB& recipeDB)
{
	std::cout<<"You will enter recipe information in [[ NAME -> DESCRIPTION -> TIME -> INGREDIENTS ]] order"<<std::endl;
    std::cout<<"Name        : "<<std::flush;	std::cin.clear();	std::cin.ignore();	std::string name;			std::getline(std::cin,name);
	std::cout<<"Description : "<<std::flush;	std::cin.clear();						std::string description;	std::getline(std::cin,description);
	std::cout<<"Time(min)   : "<<std::flush;	std::cin.clear();						int time;					std::cin>>time;
	std::cout<<"Ingredients (If you want to stop enter \"stop\" ) : "<<std::flush;
	std::vector<std::string> ingredients;
	std::cin.ignore();

	while(true)
	{		
		std::string ingredient;std::getline(std::cin,ingredient);
		if(ingredient=="stop")break;
		ingredients.push_back(ingredient);
	}

	try
	{
		Recipe* recipe = new Recipe(std::string(name.c_str()),std::string(description.c_str()),time,ingredients);
		recipeDB._insert(name, *recipe);
	}

	catch (DBException e) {
		e.resolve();
	}
}
void addPlan(PlanDB& planDB)
{	
	std::cout<<"You will enter plan information in [[ YEAR -> MONTH -> DAY -> DAYNAME -> BREAKFAST -> LUNCH -> DINNER ]] order"<<std::endl;
    std::cout<<"Year        : "<<std::flush;	std::cin.clear();	std::cin.ignore();	int year;					std::cin>>year;
    std::cout<<"Month       : "<<std::flush;	std::cin.clear();						int month;					std::cin>>month;
    std::cout<<"Day         : "<<std::flush;	std::cin.clear();						int day;					std::cin>>day;
    std::cout<<"Dayname	    : "<<std::flush;	std::cin.clear();	std::cin.ignore();	std::string dayName;		std::getline(std::cin,dayName);
	Meal breakfast = addMeal("Breakfast");
	Meal lunch 	   = addMeal("Lunch    ");
	Meal dinner	   = addMeal("Dinner   ");
	planDB._insert(Date(year,month,day),Plan(dayName.c_str(),Date(year,month,day),{breakfast,lunch,dinner}));
}
Meal addMeal(std::string mealName)
{
	std::cout<<mealName<<" (If you want to stop enter \"stop\" ) : "<<std::flush;
	std::vector<std::string> recipeList;

	while(true)
	{		
		std::string recipe;std::getline(std::cin,recipe);
		if(recipe=="stop")break;
		recipeList.push_back(recipe);
	}
	return Meal(recipeList);
}
