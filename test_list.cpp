#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.hpp"
#include "linked_list.hpp"  // include guard

constexpr std::size_t N = 2000; 

TEST_CASE("Empty constructor properly instatiates list object") {
  dsc::LinkedList<int> list;
  REQUIRE(list.empty());
}

TEST_CASE("Copy constructor is deep copy") {
   dsc::LinkedList<char> source;
   source.push_back('d');
   source.push_back('e');
   source.push_back('f');
   
   dsc::LinkedList<char> copy(source);
  
  for (size_t i = 0; i < 3; i++) {
    REQUIRE(&copy.at(i) != &source.at(i));
  }
 }

 TEST_CASE("Copy constructor copies correct values") {
   //TODO fill test
 }

TEST_CASE("Move constructor, Nonempty to empty") {
  dsc::LinkedList<char> source;
  source.push_front('a');
  source.push_front('b');
  source.push_front('c');
  dsc::LinkedList<char> moved(std::move(source));

  SECTION("Values are correct after being moved") {
    REQUIRE(moved.at(0) == 'c');
    REQUIRE(moved.at(1) == 'b');
    REQUIRE(moved.at(2) == 'a');
  }

  SECTION("Source list in move constructor nulled properly") {
    REQUIRE(source.empty());
  }

  SECTION("Move constructed list can be altered") {
    moved.push_back('d');
    REQUIRE(moved.at(3) == 'd');
  }
}

TEST_CASE("Move constructor, nonempty to nonempty") {
  dsc::LinkedList<int> source;
  source.push_back(60);
  source.push_back(61);
  source.push_back(62);

  dsc::LinkedList<int> moved(std::move(source));
}

TEST_CASE("Copy Assignment") { dsc::LinkedList<int> source; }

TEST_CASE("Insert to empty list") {
  dsc::LinkedList<char> list;
  list.insert('a', 0);
}

TEST_CASE("Insert to list with more than one element") {}
