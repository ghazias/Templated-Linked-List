#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.hpp"
#include "linked_list.hpp"  // include guard

TEST_CASE("Empty constructor properly instatiates list object") {
  dsc::LinkedList<int> int_list;
  REQUIRE(int_list.empty());
}

TEST_CASE("Copy constructor") { dsc::LinkedList<char> source; }

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
