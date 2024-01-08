#pragma once
#include <string>

enum class Gender{
	Male,
	Famale
};

class Product{
public:
	Product();
	Product(std::string productName,
			float price,
			int amount,
			int id,
			std::string type,
			std::string size,
			std::string gender);

	Product recordInput();

public:
	std::string productName_;
	float price_;
	int amount_;
	int id_;
	std::string type_;
	std::string size_;
	std::string gender_ ;
};
