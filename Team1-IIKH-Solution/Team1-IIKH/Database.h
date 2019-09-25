#pragma once
#include <string>
#include <map>
#include <iostream>

class Date;
class DBException;

template<class T1, class T2>
struct IsEqual {
	enum { value = false };
};

template<class T>
struct IsEqual<T, T> {
	enum { value = true };
};

template<class _key, class _value>
class DataBase {
protected:
	std::map<_key, _value> db;
public:
	void Insert(_key k, _value v) { db.insert(std::pair<_key, _value>(k, v)); }

	_value & Select(_key k) {
		if (db.find(k) == db.end()) {
			if (IsEqual<_key, std::string>::value) throw DBException(0, k.c_str());
			else if (IsEqual<_key, Date>::value) throw DBException(1, k.c_str());
			else throw DBException(2, k.c_str());
		}
		return (*db.find(k)).second;
	}

	void Update(_key k, _value v) {
		db.erase(k);
		db.insert(std::pair<_key, _value>(k, v));
	}

	void Delete(_key k) { db.erase(k); }
	virtual void Show(_key k) = 0;
	virtual void ShowAll() = 0;
	virtual void Save() = 0;
};

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
		case 0:
			std::cout << "Key(" << option << ") is not in DB (RecipeDB)" << std::endl;
			break;
		case 1:
			std::cout << "Key(" << option << ") is not in DB (PlanDB)" << std::endl;
			break;
		default:
			std::cout << "unknown error" << std::endl;
		}
	}
};