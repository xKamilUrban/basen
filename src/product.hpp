#pragma once
#include <string>


//Klasa abstrakcyjna zarzadzania produktem
class Product{
public:
	virtual ~Product();
	Product();
	Product(std::string productName,
			float price,
			int amount,
			int id);

	virtual void recordInput()=0;  	//Metody czysto wirtualne
	virtual void save()=0;

	void recordInputUniversal();	//Metoda wczytujaca do obiektu dane
									//uniwersalne (kazdy obiekt je zawiera)
public:
	std::string productName_;
	float price_;
	int amount_;
	int id_;
};


//Klasa pochodna zarzdzania ubraniami
class Clothes : public Product {
public:
	Clothes();
	Clothes(std::string productName,
			float price,
			int amount,
			int id,
			std::string size,
			std::string gender);
	void recordInput() override;  	//Wczytuje dane typowe dla ubran
	virtual void save() override; 	//Zapisuje obiekt w bazie danych

public:
	std::string size_;
	std::string gender_;
};


//Klasa pochodna zarzadznia sprzetem plywackim
class Equipment : public Product {
public:
	Equipment();
	Equipment(std::string productName,
			  float price,
			  int amount,
			  int id,
			  std::string size,
			  std::string advanced);
	void recordInput() override;
	virtual void save() override;

public:
	std::string size_;
	std::string advanced_;
};


//Klasa pochodna zarzadzania akcesoriami
class Accessories : public Product {
public:
	Accessories();
	Accessories(std::string productName,
				float price,
				int amount,
				int id);
	void recordInput() override;
	virtual void save() override;
};


//Klasa pochodna zarzadzania jedzeniem
class Food : public Product {
public:
	Food();
	Food(std::string productName,
		float price,
		int amount,
		int id,
		std::string weight);
	void recordInput() override;
	virtual void save() override;

public:
	std::string weight_;
};

//Klasa pochodna do wczytywania i edytowania produktu z dowolnej klasy
//pochodnej klasy Product
class ProductEdit : public Product {
public:
	ProductEdit();
	ProductEdit(std::string productName,
				float price,
				int amount,
				int id,
				std::string optional1,  //Zawiera zmienne opcjonalne,
				std::string optional2); //wystepujace tylko dla niektorych klas

	//Metoda searchname wyszukuje i usuwa produkt z bazy danych
	void searchname(std::string s);
	void recordInput() override;
	virtual void save() override;

public:
	std::string optional1_;
	std::string optional2_;
};
