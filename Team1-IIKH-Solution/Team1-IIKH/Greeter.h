#pragma once
#include <iostream>
#include <string>
#include <map>


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

// class declaration
class Greeter{
    private:
        RecipeDB recipeDB;
        PlanDB planDB;
        std::vector<std::string> menu;
    public:

    Greeter(std::vector<std::string>& _menu,RecipeDB& _recipeDB,PlanDB& _planDB):
        menu(_menu),recipeDB(_recipeDB), planDB (_planDB){    
            addMenu("SEARCH RECIPE");
            addMenu("ADD RECIPE");
            addMenu("VIEW RECIPE");
            addMenu("ADD PLAN");
            addMenu("VIEW PLAN");
            addMenu("QUIT");
        };


    
    void addMenu(std::string instruction){menu.push_back(instruction);}
    void printMenu()
    {
        std::cout<<"IIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K:::::::::::K       H:::::::::::::::::H  \n  I::::I    I::::I    K::::::K:::::K      H::::::HHHHH::::::H  \n  I::::I    I::::I    K:::::K K:::::K     H:::::H     H:::::H  \n  I::::I    I::::I  KK::::::K  K:::::KKK  H:::::H     H:::::H  \nII::::::IIII::::::IIK:::::::K   K::::::KHH::::::H     H::::::HH\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nI::::::::II::::::::IK:::::::K    K:::::KH:::::::H     H:::::::H\nIIIIIIIIIIIIIIIIIIIIKKKKKKKKK    KKKKKKKHHHHHHHHH     HHHHHHHHH"<<std::endl;
        std::cout<<"Here's Menu"<<std::endl;
        int size = menu.size();
        for(int i = 1;i<=size;i++)std::cout<<"Enter ["<<i<<"] to <"<<menu[i-1]<<">"<<std::endl;
    }
    //Add instruction to menu (Order matters)
    void selectMenu()
    {
        
        int selectedNum;std::cin>>selectedNum;
		system("CLS");
        std::cout<<"You've selected ["<<selectedNum<<"] ";
        switch (selectedNum)
        {
            case 1:
            {
				std::cout<<"to search recipe"<<std::endl;
				searchRecipe();
                break;
            }
            case 2:
            {
				std::cout<<"to add recipe"<<std::endl;
				addRecipe();
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
				addPlan();
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
    void searchRecipe()
    {
        std::cout<<"Search : "<<std::flush;
        std::cin.ignore();
        std::string searchM;std::getline(std::cin,searchM);			
        
        Recipe recipe = recipeDB._select(searchM);
        recipe.print();
    }
    void addRecipe()
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
    void addPlan()
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
};