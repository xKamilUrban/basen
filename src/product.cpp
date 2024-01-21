#include "product.hpp"
#include "databaseShop.hpp"
#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Implementacja klas z pliku product.hpp

Product::Product() : price_(), amount_(), id_()
{}

Product::Product(std::string productName,
				float price,
				int amount,
				int id)
	: productName_(productName)
	, price_(price)
	, amount_(amount)
	, id_(id)
{}

Product:: ~Product() {}


Clothes::Clothes() : Product(), size_(), gender_()
{}

Clothes::Clothes(std::string productName,
				float price,
				int amount,
				int id,
				std::string size,
				std::string gender)
    : Product(productName, price, amount, id)
	, size_(size)
	, gender_(gender)
{}


Equipment::Equipment() : Product(), size_(), advanced_()
{}

Equipment::Equipment(std::string productName,
					float price,
					int amount,
					int id,
					std::string size,
					std::string advanced)
    : Product(productName, price, amount, id)
	, size_(size)
	, advanced_(advanced)
{}


Accessories::Accessories() : Product()
{}

Accessories::Accessories(std::string productName,
						float price,
						int amount,
						int id)
    : Product(productName, price, amount, id)
{}


Food::Food() : Product()
{}

Food::Food(std::string productName,
		   float price,
		   int amount,
		   int id,
		   std::string weight)
    : Product(productName, price, amount, id)
	, weight_(weight)
{}

ProductEdit::ProductEdit() : Product()
{}

ProductEdit::ProductEdit(std::string productName,
		   	   	   	   	 float price,
						 int amount,
						 int id,
						 std::string optional1,
						 std::string optional2)
    : Product(productName, price, amount, id)
	, optional1_(optional1)
	, optional2_(optional2)
{}


//Metoda do wczytywania danych uniwersalnych do obiektu
//Metoda przypisuje wczytane dane do obiektu
void Product::recordInputUniversal() {
	Menu menu;
    std::string name,amount_st,price_st;
    int amount;
    float price;

    // Wprowadzanie danych od uzytkownika

    std::cout<<"Podaj nazwe produktu: ";
    std::cin>>name;
    //string_check sprawdza czy nazwa nie jest nazwa nie jest liczba
    name=menu.string_check(name);

    std::cout<<"Podaj cene: ";
    std::cin>>price_st;
    //type_check_float sprawdza czy podano typ float i max dwa miejsca po przecinku
    price=menu.type_check_float(price_st,price_st.length());

    //Cena i ilosc produktow jest ograniczona w [0,999]
    while(price>999 or price<=0){
    	std::cout<<"Przekroczono zakres"<<std::endl;
        std::cout<<"Podaj cene: ";
        std::cin>>price_st;
        price=menu.type_check_float(price_st,price_st.length());
    }
    std::cout<<"Podaj ilosc towaru: ";
    std::cin>>amount_st;
    amount=menu.type_check(amount_st,-1);	//czy podano typ int
    while(amount>999 or amount<=0){
    	std::cout<<"Przekroczono zakres"<<std::endl;
        std::cout<<"Podaj ilosc towaru: ";
        std::cin>>amount_st;
        amount=menu.type_check(amount_st,-1);	//czy podano typ int
    }
    productName_ = name;
    price_ = price;
    amount_ = amount;
}


//Meotda do wczytywania rozmiaru i przeznaczania (wzgl. plci) dla ubran
void Clothes::recordInput(){
	std::string size, gender;
	Menu menu;

	std::cout<<"Podaj rozmiar: ";
	std::cin>>size;
	size=menu.string_check(size);		//czy nie podano liczby
	std::cout<<"Dla jakiej plci przeznaczony jest produkt: ";
	std::cin>>gender;
	gender=menu.string_check(gender);	//czy nie podano liczby

	size_ = size;
	gender_ = gender;
}

//Meotda do wczytywania rozmiaru i przeznaczania (wzgl. zaawansowania) dla sprzetu
void Equipment::recordInput(){
	std::string size, advanced;
	Menu menu;
	std::cout<<"Podaj rozmiar: ";
	std::cin>>size;
	size=menu.string_check(size);		//czy nie podano liczby
	std::cout<<"Podaj zaawansowanie: ";
	std::cin>>advanced;
	advanced=menu.string_check(advanced);	//czy nie podano liczby


	size_ = size;
	advanced_ = advanced;
}

void Accessories::recordInput(){

}

//Metoda do wczytywania wagi/objetosci jedzenia
void Food::recordInput(){
	std::string weight_st;
	int weight;
	Menu menu;
	std::cout<<"Podaj wage/obietosc: ";
	std::cin>>weight_st;
    weight=menu.type_check(weight_st,-1);	//czy podano typ int
    while(weight>999 or weight<=0){
    	std::cout<<"Przekroczono zakres"<<std::endl;
        std::cout<<"Podaj ilosc towaru: ";
        std::cin>>weight_st;
        weight=menu.type_check(weight_st,-1);	//czy podano typ int
    }

	weight_ = std::to_string(weight);
}

void ProductEdit::recordInput(){}


//Metoda do zapisu obiektow klasy ubrania w pliku product.txt
//Metoda save dla kazdej klasy zapewnia zachowanie odpowiedniej
//struktury bazy danych w pliku product.txt

//Ubrania sa zapisywane do pliku product.txt pomiedzy linia [00]
//a ostatnim obiektem
void Clothes::save(){
	std::ofstream tempOut,fout;
	std::ifstream tempIn,fin;
	tempIn.open("temp.txt");
	tempOut.open("temp.txt");
	fin.open("product.txt");
	fout.open("product.txt",std::ios::app);
	std::string line;

	//Odczytywanie pliku product.txt linia po lini
	while (std::getline(fin, line)){
		//Wystepuje linia [00], obiekt jest zapisywany do temp.txt
		if(line.find("[00]") != std::string::npos){
			tempOut<<productName_<<" ";
			tempOut<<id_<<" ";
			tempOut<<amount_<<" ";
			tempOut<<price_<<" ";
			tempOut<<size_<<" ";
			tempOut<<gender_<<" ";
			tempOut<<std::endl;
			//[00] jest zapisywane do temp.txt
			tempOut<<line<<std::endl;
		}
		//Przeciwnie linia jest przepisywana do temp.txt
		else{
			tempOut<<line<<std::endl;
		}
	}
	//temp.txt ma odpowiednia sktukture i zawiera dopisany obiekt
	fout.close();
	fout.open("product.txt",std::ios::trunc);
	fout.close();
	fout.open("product.txt",std::ios::app);
	//Przepisanie  temp.txt do product.txt
	fout<<tempIn.rdbuf();
	tempIn.close();
	tempOut.close();
	fin.close();
	fout.close();
}

//Sprzet jest zapisywany do pliku product.txt pomiedzy linia [01]
//a ostatnim obiektem
void Equipment::save(){
	std::ofstream tempOut,fout;
	std::ifstream tempIn,fin;
	tempIn.open("temp.txt");
	tempOut.open("temp.txt");
	fin.open("product.txt");
	fout.open("product.txt",std::ios::app);
	std::string line;

	while (std::getline(fin, line)){
		if(line.find("[01]") != std::string::npos){
			tempOut<<productName_<<" ";
			tempOut<<id_<<" ";
			tempOut<<amount_<<" ";
			tempOut<<price_<<" ";
			tempOut<<size_<<" ";
			tempOut<<advanced_<<" ";
			tempOut<<std::endl;
			tempOut<<line<<std::endl;
		}
		else{
			tempOut<<line<<std::endl;
		}
	}
	fout.close();
	fout.open("product.txt",std::ios::trunc);
	fout.close();
	fout.open("product.txt",std::ios::app);
	fout<<tempIn.rdbuf();
	tempIn.close();
	tempOut.close();
	fin.close();
	fout.close();
}

//Akcesoria sa zapisywane do pliku product.txt pomiedzy linia [02]
//a ostatnim obiektem
void Accessories::save(){
	std::ofstream tempOut,fout;
	std::ifstream tempIn,fin;
	tempIn.open("temp.txt");
	tempOut.open("temp.txt");
	fin.open("product.txt");
	fout.open("product.txt",std::ios::app);
	std::string line;

	while (std::getline(fin, line)){
		if(line.find("[02]") != std::string::npos){
			tempOut<<productName_<<" ";
			tempOut<<id_<<" ";
			tempOut<<amount_<<" ";
			tempOut<<price_<<" ";
			tempOut<<std::endl;
			tempOut<<line<<std::endl;
		}
		else{
			tempOut<<line<<std::endl;
		}
	}
	fout.close();
	fout.open("product.txt",std::ios::trunc);
	fout.close();
	fout.open("product.txt",std::ios::app);
	fout<<tempIn.rdbuf();
	tempIn.close();
	tempOut.close();
	fin.close();
	fout.close();
}

//Jedzenie jest zapisywane do pliku product.txt pomiedzy linia [03]
//a ostatnim obiektem
void Food::save(){
	std::ofstream tempOut,fout;
	std::ifstream tempIn,fin;
	tempIn.open("temp.txt");
	tempOut.open("temp.txt");
	fin.open("product.txt");
	fout.open("product.txt",std::ios::app);
	std::string line;

	while (std::getline(fin, line)){
		if(line.find("[03]") != std::string::npos){
			tempOut<<productName_<<" ";
			tempOut<<id_<<" ";
			tempOut<<amount_<<" ";
			tempOut<<price_<<" ";
			tempOut<<weight_<<" ";
			tempOut<<std::endl;
			tempOut<<line<<std::endl;
		}
		else{
			tempOut<<line<<std::endl;
		}
	}
	fout.close();
	fout.open("product.txt",std::ios::trunc);
	fout.close();
	fout.open("product.txt",std::ios::app);
	fout<<tempIn.rdbuf();
	tempIn.close();
	tempOut.close();
	fin.close();
	fout.close();
}

void ProductEdit::save(){}

//Metoda wyszukuje w pliku product.txt wzorca s identyfikowanego z
//szukanym obiektem. Wyszukany obiekt jest domyslnie usuwany z pliku.
void ProductEdit::searchname(std::string s){
	std::ofstream tempOut,fout;
	std::ifstream tempIn,fin;
	tempIn.open("temp.txt");
	tempOut.open("temp.txt");
	fin.open("product.txt");
	std::string line;

	//Odczytywanie pliku porduct.txt linia po lini
	while(std::getline(fin,line)){
		//Znalezienie wzorca, dane z lini sa podstawiane do obiektu.
		if (line.find(s)!= std::string::npos){
			std::istringstream iss(line);
			iss >> productName_ >>id_>>amount_ >>price_>> optional1_ >> optional2_;
		}
		//Przeciwnie linia jest przepisywana do temp.txt
		else{
			tempOut<<line<<std::endl;
		}
	}
	//Plik temp.txt zawiera cala baze z pliku product.txt poza wyszukanym obiektem
	fout.open("product.txt");
	//Przepisanie  temp.txt do product.txt
	fout<<tempIn.rdbuf();
	tempIn.close();
	tempOut.close();
	fin.close();
	fout.close();
}
