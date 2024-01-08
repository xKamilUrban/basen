#include <iostream>
#include "databaseShop.hpp"
#include "product.hpp"

int main(){
	Product stroj {
		"stroj damski w kropki",  //nazwa produktu
		199, //cena
		120, //ilosc produktow
		3430032, // id produktu
		"odziez", //typ produktu
		"M", //rozmiar
		"Damskie" //dla jakiej plci jest przeznaczony
	};
	DatabaseShop db;
	db.add(stroj);
	std::cout<< db.print(stroj);

	return 0;
}
