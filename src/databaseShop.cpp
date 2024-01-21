#include "databaseShop.hpp"
#include "product.hpp"
#include <iostream>
#include <fstream>
#include <string>

//Metoda dodaje produkt dowolnego typu do bazy danych.
void DatabaseShop::add(const ProductEdit& pr){
	int first;
	first=pr.id_/1000;
	//if sprawdzaja jakiego typu produktem jest pr
	//sprawdzana jest pierwsza cyfra id
	if(first==1){
		Clothes C;						//Tworzony jest puty obietk C do ktorego
		C.productName_=pr.productName_;				//przypisywane sa dane obiektu pr
		C.price_=pr.price_;
		C.amount_=pr.amount_;
		C.id_=pr.id_;
		C.size_=pr.optional1_;
		C.gender_=pr.optional2_;
		C.save();						//Obiekt jest zapisywany do product.txt
	}								//metoda save z klasy Clothes
	else if(first==2){
		Equipment E;
		E.productName_=pr.productName_;
		E.price_=pr.price_;
		E.amount_=pr.amount_;
		E.id_=pr.id_;
		E.size_=pr.optional1_;
		E.advanced_=pr.optional2_;
		E.save();
	}
	else if(first==3){
		Accessories A;
		A.productName_=pr.productName_;
		A.price_=pr.price_;
		A.amount_=pr.amount_;
		A.id_=pr.id_;
		A.save();
	}
	else if(first==4){
		Food F;
		F.productName_=pr.productName_;
		F.price_=pr.price_;
		F.amount_=pr.amount_;
		F.id_=pr.id_;
		F.weight_=pr.optional1_;
		F.save();
	}
}

//Metoda wypisujaca dane obiektu
std::string DatabaseShop::print(const ProductEdit& s) const{
	return "Nazwa produktu: "+ s.productName_ + "\n"
		+"Cena: "+ std::to_string(s.price_) + "\n"
		+"Dostepne sztuki: "+ std::to_string(s.amount_) + "\n";
}

//Metoda na podstawie otrzymanego jako argument id
//Wczutuje dane do obiektu i zapisuje go odpowiednia metoda
//w pliku product.txt. Wczytywanie ze strumienia wejscia
void DatabaseShop::Input(int id){
	int first;
	first = id/1000;

	if(first==1){
		Clothes C;				//Tworzony jest pusty obiekt i
		C.recordInputUniversal();		//wczytywana jest metoda recordInput
		C.recordInput();			//z klasy odpowiedniej dla typu obiektu
		C.id_=id;
		C.save();
	}
	else if(first==2){
		Equipment E;
		E.recordInputUniversal();
		E.recordInput();
		E.id_=id;
		E.save();
	}
	else if(first==3){
		Accessories A;
		A.recordInputUniversal();
		A.recordInput();
		A.id_=id;
		A.save();
	}
	else if(first==4){
		Food F;
		F.recordInputUniversal();
		F.recordInput();
		F.id_=id;
		F.save();
	}
}


//Metoda wyswietla odpowiednia czesc bazy danych z product.txt
//od lini start do lini end
void DatabaseShop::DisplayDB(std::string start,std::string end){
	std::ifstream fin;
	fin.open("product.txt");
	std::string line;

	bool display=false;
	int i=0;
	//product.txt jest wczytywany linia po lini
	while (std::getline(fin, line) or display==true) {
		if (line.find(start) != std::string::npos) {
			display = true;
		}

		//W momencie wystapienia lini end display osiaga wartosc true
		//Tzn. linie sa wyswietlane od momentu wystapienia lini start
		if (display) {
			//Linia start oraz end nie sa wyswietlane
			if(line!=start and line!=end){
				i++;
				std::cout<<i<<".";
				std::cout << line << std::endl;
			}
		}

		//Wystepuje linia end, display osiaga wartos false
		//wyswietlanie zostaje zakonczone
		if (line.find(end) != std::string::npos) {
			display = false;
		}
	}
	fin.close();
}
