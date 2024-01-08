#include "databaseShop.hpp"
#include "product.hpp"
#include <iostream>
#include <fstream>

bool DatabaseShop::add(const Product& s){
	if(!exist){
		std::ofstream fout;
		fout.open("/Users/gosc/Documents/abc.txt",std::ios::app);
		fout<<s.id_<<"     ";
		fout<<s.price_<<"   ";
		fout<<s.amount_<<"   ";
		fout<<s.productName_<<"   ";
		fout<<s.type_<<"   ";
		fout<<s.size_<<"   ";
		fout<<s.gender_<<"   ";
		fout<<std::endl;
		fout.close();
		exist=true;
		return true;
	}
	else{
		return false;
	}
}


std::string DatabaseShop::print(const Product& s) const{
	return "Nazwa produktu: "+ s.productName_ + "\n"
		+"Cena: "+ std::to_string(s.price_) + "\n"
		+"Dostepne sztuki: "+ std::to_string(s.amount_) + "\n"
		+"Typ: "+ s.type_ + "\n"
		+"Rozmiar: "+ s.size_ + "\n"
		+ s.gender_ + "\n";
}
