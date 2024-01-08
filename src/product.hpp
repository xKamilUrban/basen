#pragma once
#include <string>

enum class Gender{
	Male,
	Famale
};

class Product{
public:
	Product(std::string productName,
			float price,
			int amount,
			int id,
			std::string type,
			std::string size,
			Gender gender);

private:
	Gender g;
};
