#pragma once
#include "product.hpp"

class DatabaseShop{
public:
	bool add(const Product & pr);
private:
	bool exist=false;
};
