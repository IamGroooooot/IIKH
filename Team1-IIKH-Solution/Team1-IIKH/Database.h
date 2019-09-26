#pragma once
#include <string>
#include <map>
#include <iostream>

//Class declaration
class Date;
class DBException;


//Template declaration
template<class T1, class T2>
struct IsEqual {
	enum { value = false };
};

template<class T>
struct IsEqual<T, T> {
	enum { value = true };
};

template<class _key, class _value>


//Control entire DB system
class DataBase {

protected:

	std::map<_key, _value> db;

public:

	//Insert pair of key and value
	void Insert(_key k, _value v) { db.insert(std::pair<_key, _value>(k, v)); }



	_value & Select(_key k) {


		//If you do not find key (throws exception)
		if (db.find(k) == db.end()) {
			if (IsEqual<_key, std::string>::value) throw DBException(0, k.c_str());
			else if (IsEqual<_key, Date>::value) throw DBException(1, k.c_str());
			else throw DBException(2, k.c_str());
		}


		//If you find key (return value)
		return (*db.find(k)).second;
	}


	//Delete pair of key and value, insert new pair of key and value
	void Update(_key k, _value v) { 
		db.erase(k);
		db.insert(std::pair<_key, _value>(k, v));
	}


	//Delete pair of key and value
	void Delete(_key k) { db.erase(k); }



	virtual void Show(_key k) = 0;



	virtual void ShowAll() = 0;



	virtual void Save() = 0;
};



//Handle DB related error
class DBException {

private:

	int error;
	std::string option;


public:

	DBException(int e, const char * s) :
		error(e), option(s) {};


	void resolve() {


		std::cout << "DB error (" << error << ") : ";
		

		switch (error) {
			
			//No searching key in RecipeDB
			case 0:
				std::cout << "Key(" << option << ") is not in DB (RecipeDB)" << std::endl;
				break;

			//No searching key in PlanDB
			case 1:
				std::cout << "Key(" << option << ") is not in DB (PlanDB)"   << std::endl;
				break;

			default:
				std::cout << "unknown error" << std::endl;
		}
	}
};