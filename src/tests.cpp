#include <gtest/gtest.h>
#include "databaseShop.hpp"
#include "product.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(CheckStructure, ProductRecord){
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
	EXPECT_TRUE(db.add(stroj));
	EXPECT_FALSE(db.add(stroj));
};

//TEST(DisplayDB, NonEmpty){
//	Product stroj {
//		"stroj damski w kropki",  //nazwa produktu
//		199, //cena
//		120, //ilosc produktow
//		3430032, // id produktu
//		"odziez", //typ produktu
//		"M", //rozmiar
//		Gender::Famale //dla jakiej plci jest przeznaczony
//	};
//	DatabaseShop db;
//	EXPECT_TRUE(db.add(stroj));
//
//	auto content = db.print(stroj);
//	auto expected = "stroj damski w kropki "
//					"cena: 199zl "
//					"ilosc dostepnych produtkow: 120 "
//					"rozmiar: M ";
//	EXPECT_EQ(content, expected);
//	db.DisplayDB();
//};
