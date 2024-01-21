#include "databaseShop.hpp"
#include "product.hpp"
#include "menu.hpp"
#include <iostream>
#include <cctype>
#include <string>
#include <cmath>

//type_check sprawdza czy wprowadzana zmienna s jest
//dlugosci len i sklada sie z cyfr, zmienia jej typ na int
int Menu::type_check(std::string s,int len){
	bool correct=false;
	int choice;
	while(!correct){
		//Proba zmiany s na int. W przypadku powodzenia
		//petla zostaje zakonczona
		try{
			choice=std::stoi(s);
			correct=true;
		}
		//w przypadku niepowodzenia wymuszane
		//jest ponowne podanie zmiennej
		catch (const std::invalid_argument&){
			correct=false;
			std::cout << "Niepoprawny wybor. Sprobuj ponownie." << std::endl;
			std::cin >> s;
		}
		if(s.size()!=len and len!=-1){
			s="incorrect_len";			//Nieprawidlowa dlugosc, s jest
			correct=false;				//zamianiana na string aby try rzucil wyjatek.
		}								//len=-1 wylacza opcje sprawdzania dlugosc.
	}
	return choice;
}

//Metoda sprawdza czy cena prduktu jest wprowadzana w poprawnej formie
float Menu::type_check_float(std::string s,int len){
	bool correct=false;
	float choice,floor,frac,epsilon;
	epsilon=1e-6;
	while(!correct){
		//W przypadku powodzenia wyznaczana jest frac
		//w celu sprawdzenia czy po 2 miejscu po przecinku
		//wystepuja cyfry w liczbe typu float
		try{
			choice=std::stof(s);
			correct=true;
			frac = modf(100*choice, &floor);
		}
		catch (const std::invalid_argument&){
			correct=false;
			std::cout << "Niepoprawny wybor. Sprobuj ponownie." << std::endl;
			std::cin >> s;
		}
		//Sprawdzenie czy frac jest zerem
		if(correct and frac>epsilon){
			correct=false;
			s="incorrect_len";
		}
	}
	return choice;
}

//Metoda sprawdza czy podana s nie jest liczba
std::string Menu::string_check(std::string s){
	bool correct=false;
	while(!correct){
		try{
			std::stoi(s);
			std::cout<<"Blad. Podano liczbe. Sprobuj ponownie"<<std::endl;
			std::cin >> s;
			correct=false;
		}
		catch (const std::invalid_argument&){
			correct=true;
		}
	}
	return s;
}

//Metoda wczytujaca menu glowne sklepu
void Menu::mainMenu(){
	DatabaseShop db;
	Menu menu;
	int id,first,choice;
	std::string choice_,id_st;
	ProductEdit productedit;
	do{
		std::cout << "==== Menu zarzadzania sklepem ====" << std::endl;
		std::cout << "0. Powrot" << std::endl;
		std::cout << "1. Wyswietalnie bazy danych" << std::endl;
		std::cout << "2. Zarzadzanie produktem" << std::endl;
		std::cout << "3. Dodawanie nowych produktow" << std::endl;
		std::cin >> choice_;
		choice=type_check(choice_,1);

		switch(choice){
			case 0:
				break;
			case 1:
				menu.databaseMenu(); //Menu zarzadania baza danych
				break;
			case 2:
				menu.productMenu(); //Menu zarzadzania produktem
				break;
			case 3:
				std::cout << "Dodawanie produktu" << std::endl;
				std::cout << "Pierwsza cyfra id musi miec wartosc:" << std::endl;
				std::cout << "1-Ubrania, 2-Sprzet Sportowy, 3-Akcesoria 4-Jedzenie" << std::endl;
				std::cout << "Podaj id produktu:";
				std::cin >> id_st;
				//Sprawdznie czy id jest typu int i ma dlougosc 4
				id=type_check(id_st,4);
				//searchname wyszukuje produkt o podanym id w pliku product.txt
				//i podstawia dane pod obiekt productedit
				productedit.searchname(id_st);
				//id jest rozne od zera, produkt istnieje, wymuszane jest ponowne podanie id
				while(productedit.id_!=0){
					db.add(productedit);	//searchname usuwa produkt wiec nalezy go ponownie dodac
					productedit.id_=0;
					std::cout<<"Pordukt o podanym id juz istnieje. Sprobuj ponownie"<<std::endl;
					std::cin >> id_st;
					id=type_check(id_st,4);
					productedit.searchname(id_st);
				}
				first=id/1000;
				//Sprawdzanie poprawnosci podania id
				while(first>4 or first<1){
					std::cout << "Pierwsza cyfra id niepoprawna" <<std::endl;
					std::cout << "Podaj poprawne id:";
					std::cin >> id_st;
					id=type_check(id_st,4);
					first=id/1000;
				}
				//Wywolanie metody wczytujacej z klawiatury dane obiektu i
				//zapisujacej obiekt w product.txt
				db.Input(id);
				break;
			default:
				std::cout << "Niepoprawny wybor. Sprobuj ponownie." << std::endl;
		}
	}while(choice!=0);
}

//Menu zarzadzania baza danych
void Menu::databaseMenu(){
	int choice;
	std::string choice_;
	DatabaseShop db;
	Menu menu;
	do{
		std::cout << "0. Powrot" << std::endl;
		std::cout << "1. Wyswietalnie calej bazy danych" << std::endl;
		std::cout << "2. Wyswietalnie bazy danych ubran" << std::endl;
		std::cout << "3. Wyswietalnie bazy danych sprzetu plywackiego" << std::endl;
		std::cout << "4. Wyswietalnie bazy danych akcesoriow" << std::endl;
		std::cout << "5. Wyswietalnie bazy danych zywnosci" << std::endl;
		std::cin >> choice_;
		choice=type_check(choice_,1);	//Sprawdzenie czy choice jest poprawnego typu

		switch(choice){
			case 0:
				break;
			case 1:
				std::cout << "Ubrania:" << std::endl;
				//Wyswietlanie product.txt od [0] do [00]
				db.DisplayDB("[0]","[00]");
				std::cout << "Sprzęt pływacki:" << std::endl;
				db.DisplayDB("[00]","[01]");
				std::cout << "Akcesoria:" << std::endl;
				db.DisplayDB("[01]","[02]");
				std::cout << "Żywność:" << std::endl;
				db.DisplayDB("[02]","[03]");
				break;
			case 2:
				std::cout << "Baza danych ubran" << std::endl;
				db.DisplayDB("[0]","[00]");
				break;
			case 3:
				std::cout << "Baza danych sprzetu plywackiego" << std::endl;
				db.DisplayDB("[00]","[01]");
				break;
			case 4:
				std::cout << "Baza danych akcesoriow" << std::endl;
				db.DisplayDB("[01]","[02]");
				break;
			case 5:
				std::cout << "Baza danych zywnosci" << std::endl;
				db.DisplayDB("[02]","[03]");
				break;
			default:
				std::cout << "Niepoprawny wybor. Sprobuj ponownie." << std::endl;
		}
	}while(choice!=0);
}

//Menu zarzadzania produktem
void Menu::productMenu(){
	int choice,id,amount;
	DatabaseShop db;
	ProductEdit productedit;
	Menu menu;
	bool exist=false,del=false;
	std::string id_st,choice_,name,amount_st,price_st;
	float price;
	do{
		std::cout << "0. Powrot" << std::endl;
		std::cout << "Wpisz czterocyfrowe id produktu:";
		std::cin >> id_st;
		//podano 0, powrot
		if(id_st=="0"){
			choice=0;
			break;
		}

		//Sprawdzenie czy produkt o podanym id istnieje
		while(!exist){
			id=type_check(id_st,4);	//sprawdanie poprawnosci typu id
			while(id/1000<1){
				std::cout << "Id niepoprawne.Sprobuj ponownie"<< std::endl;
				std::cin >> id_st;
				id=type_check(id_st,4);
			}
			id_st=std::to_string(id);	//serachname otrymuje na wejsciu string
			productedit.searchname(id_st);
			if(productedit.id_==0){
				std::cout << "Produkt nie istnieje.Sprobuj ponownie"<< std::endl;
				std::cin >> id_st;
				exist=false;
			}
			else{
				exist=true;
			}
		}
		std::cout << "Wybrany produkt: " << std::endl;
		std::cout<<db.print(productedit);	//Wypisanie na ekranie danych obiektu

		//Zarzadanie wybranym produktem
		do{
			std::cout << "0. Powrot" << std::endl;
			std::cout << "1. Usun produkt" << std::endl;
			std::cout << "2. Edytuj nazwe" << std::endl;
			std::cout << "3. Edytuj cene" << std::endl;
			std::cout << "4. Edytuj ilosc dostepnych produktow" << std::endl;
			std::cin >> choice_;
			choice=type_check(choice_,1);

			switch(choice){
				case 0:
					break;
				case 1:
					std::cout << "Produkt usuniety" << std::endl;
					choice=0;
					del=true;	//Oznaczenie produktu jako do usuniecia
					break;
				case 2:
					std::cout << "Wpisz nową nazwe: ";
					std::cin>>name;
					name=string_check(name);	//Sprawdzanie czy name nie jest liczba
					std::cout<<std::endl;
					productedit.productName_=name;	//Zmiana nazwy produktu
					std::cout << "Nazwa zostala zmieniona " << std::endl;
					break;
				case 3:
					std::cout << "Wpisz nową cene: " << std::endl;
					std::cin>>price_st;
					price=type_check_float(price_st,price_st.length());	//sprawdznie poprawnosci podanej ceny
				    while(price>999 or price<=0){	//sprawdzenie czy cena zawiera sie w [0,999]
				    	std::cout<<"Przekroczono zakres"<<std::endl;
				        std::cout<<"Podaj cene: ";
				        std::cin>>price_st;
				        price=menu.type_check_float(price_st,price_st.length());
				    }
					std::cout<<std::endl;
					productedit.price_=price;
					std::cout << "Cena została zmieniona " << std::endl;
					break;
				case 4:
					std::cout << "Wpisz ilosc dostępnych produktow: " << std::endl;
					std::cin>>amount_st;
					amount=type_check(amount_st,-1);
				    while(amount>999 or amount<=0){
				    	std::cout<<"Przekroczono zakres"<<std::endl;
				        std::cout<<"Podaj ilosc towaru: ";
				        std::cin>>amount_st;
				        amount=menu.type_check(amount_st,-1);
				    }
					std::cout<<std::endl;
					productedit.amount_=amount;
					std::cout << "Ilosc produktow zostala zmieniona " << std::endl;
						break;
				default:
					std::cout << "Niepoprawny wybor. Sprobuj ponownie." << std::endl;
			}
		}while(choice!=0);
	}while(choice!=0);
	//Produkt nie do usuniacia, nalezy go zapisac.
	//searchname domyslnie usunal produkt
	if(del==false){
		db.add(productedit);
	}
}
