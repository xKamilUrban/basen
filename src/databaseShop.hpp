#pragma once
#include <vector>
#include "product.hpp"

class DatabaseShop{
public:
	void DisplayDB(std::string start,std::string end);
	std::string print(const ProductEdit& s) const;
	void add(const ProductEdit& pr);
	void Input(int id);
private:
	bool exist=false;
	std::vector<Product> products_;
};
