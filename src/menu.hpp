#pragma once
#include "product.hpp"
#include "databaseShop.hpp"
#include <string>

class Menu{
public:
	void mainMenu();
	void databaseMenu();
	void productMenu();
	int type_check(std::string,int);
	float type_check_float(std::string,int);
	std::string string_check(std::string);
};
