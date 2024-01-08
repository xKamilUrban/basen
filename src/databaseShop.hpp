#pragma once
#include <vector>
#include "product.hpp"

class DatabaseShop{
public:
	bool add(const Product& pr);
	void DisplayDB() const;
	std::string print(const Product& s) const;
	int searchname(std::string);
private:
	bool exist=false;
	std::vector<Product> products_;
};
