#include "product.hpp"
#include <iostream>
Product::Product() : price_(), amount_(), id_()
{}

Product::Product(std::string productName,
				float price,
				int amount,
				int id,
				std::string type,
				std::string size,
				std::string gender)
	: productName_(productName)
	, price_(price)
	, amount_(amount)
	, id_(id)
	, type_(type)
	, size_(size)
	, gender_(gender)
{}

Product Product::recordInput() {
    Product newProduct;
    std::string name, type, size,gender;
    int amount, id;
    float price;
    std::cout<<"Podaj nazwe produktu: ";
    std::cin>>name;
    std::cout<<"Podaj cene: ";
    std::cin>>price;
    std::cout<<"Podaj ilosc towaru: ";
    std::cin>>amount;
    std::cout<<"Podaj id: ";
    std::cin>>id;
    std::cout<<"Podaj typ: ";
    std::cin>>type;
    std::cout<<"Podaj rozmiar: ";
    std::cin>>size;
    std::cout<<"Towar meski czy damski: ";
    std::cin>>gender;
    newProduct.productName_ = name;
    newProduct.price_ = 123.0;
    newProduct.amount_ = 20;
    newProduct.id_ = 1234;
    newProduct.type_ = "xx";
    newProduct.size_ = "xd";
    newProduct.gender_ = "ds";

    return newProduct;
}
