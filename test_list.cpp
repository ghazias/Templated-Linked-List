#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.hpp"
#include "linked_list.hpp"  // include guard

constexpr std::size_t N = 2000;

TEST_CASE("Empty constructor properly instatiates list object") {
  dsc::LinkedList<int> list;
  REQUIRE(list.empty());
}

TEST_CASE("Copy constructor") {
  dsc::LinkedList<char> source;
  source.push_back('d');
  source.push_back('e');
  source.push_back('f');

  dsc::LinkedList<char> copy(source);
  SECTION(" is deep copy") {
    for (size_t i = 0; i < 3; i++) {
      REQUIRE(&copy.at(i) != &source.at(i));
    }
  }

  SECTION(" has correct values") {
    for (std::size_t i = 0; i < 3; ++i) {
      REQUIRE(copy.at(i) == source.at(i));
    }
  }
}

TEST_CASE("Move constructor") {
  dsc::LinkedList<char> source;
  source.push_front('a');
  source.push_front('b');
  source.push_front('c');

  char* addresses[] = {&source.at(0), &source.at(1), &source.at(2)};
  dsc::LinkedList<char> moved(std::move(source));

  SECTION(" has correct values") {
    REQUIRE(moved.at(0) == 'c');
    REQUIRE(moved.at(1) == 'b');
    REQUIRE(moved.at(2) == 'a');
  }

  SECTION("Source list in move constructor nulled properly") {
    REQUIRE(source.empty());
  }

  SECTION("Move constructed list can be altered") {
    moved.push_front('d');
    REQUIRE(moved.at(0) == 'd');
  }

  SECTION(" values have not moved in memory") {
    for (std::size_t i = 0; i < 3; ++i) REQUIRE(&moved.at(i) == addresses[i]);
  }
}

// TODO different size list tests
TEST_CASE("Nonempty copy assignment") {
  dsc::LinkedList<int> source;
  source.push_back(60);
  source.push_back(61);
  source.push_back(62);

  int* addresses[] = {&source.at(0), &source.at(1), &source.at(2)};

  SECTION("Empty =") {
    dsc::LinkedList<int> copy = source;
    for (std::size_t i = 0; i < 3; ++i) {
      REQUIRE(copy.at(i) == source.at(i));
      REQUIRE(&copy.at(i) != addresses[i]);
    }
  }

  SECTION("Nonempty =") {
    dsc::LinkedList<int> copy;
    copy.push_back(20);
    copy.push_back(21);
    copy.push_back(22);

    copy = source;

    for (std::size_t i = 0; i < 3; ++i) {
      REQUIRE(copy.at(i) == source.at(i));
      REQUIRE(&copy.at(i) != addresses[i]);
    }
  }

  SECTION("Self =") {
    source = source;
    for (std::size_t i = 0; i < 3; ++i) {
      REQUIRE(&source.at(i) == addresses[i]);
    }
  }
}

TEST_CASE("Empty copy assignment") {
  dsc::LinkedList<int> source;
  REQUIRE(source.empty());

  SECTION("Empty =") {
    dsc::LinkedList<int> copy = source;
    REQUIRE(copy.empty());
    REQUIRE(&copy != &source);
  }

  SECTION("Nonempty =") {
    dsc::LinkedList<int> copy;
    copy.push_back(69);
    copy.push_back(88);
    copy.push_back(103);

    REQUIRE_FALSE(copy.empty());
    copy = source;
    REQUIRE(copy.empty());
  }
}

TEST_CASE("== operator") {
  // == on equal list
  // == on non-equals list
}

TEST_CASE("Move assignment ") {}

TEST_CASE("size() of empty list") {}

TEST_CASE("size() of nonempty list") {}

TEST_CASE("empty() of empty list") {
  dsc::LinkedList<long> empty;
  REQUIRE(empty.empty());
}

TEST_CASE("empty() of nonempty list") {
  dsc::LinkedList<short> nonempty;
  nonempty.push_back(8);
  nonempty.push_back(9);
}

TEST_CASE("at()") {
  dsc::LinkedList<std::string> list;
  list.push_back("lorem");
  list.push_back("ipsum");
  list.push_back("dolor");

  std::string* addresses[] = {&list.at(0), &list.at(1), &list.at(2)};

  SECTION("const version returns correct values") {
    REQUIRE(list.at(2) == "lorem");
    REQUIRE(list.at(1) == "ipsum");
    REQUIRE(list.at(0) == "dolor");
  }

  SECTION("Non-const version allows for value changes") {
    list.at(0) = "spelunking";
    REQUIRE(list.at(0) == "spelunking");
    REQUIRE(list.at(1) == "ipsum");
    REQUIRE(list.at(2) == "dolor");
  }

  SECTION("Throws exception with invalid index") {
    REQUIRE_THROWS(list.at(80));
  }
}

TEST_CASE("push_front() cases") {
  dsc::LinkedList<char> list;

  list.push_front('j');  // empty list push
  REQUIRE(list.at(0) == 'j');

  list.push_front('k');  // single element list push
  REQUIRE(list.at(0) == 'k');
  REQUIRE(list.at(1) == 'j');

  list.push_front('l');  // multiple element list push
  REQUIRE(list.at(0) == 'l');
  REQUIRE(list.at(1) == 'k');
  REQUIRE(list.at(2) == 'j');
}

TEST_CASE("push_front() stress test") {
  constexpr std::size_t N = 2000;
  dsc::LinkedList<std::size_t> list;

  for (std::size_t i = 0; i < N; ++i) {
    list.push_back(i);
  }

  for (std::size_t i = 0; i < N; ++i) {
    REQUIRE(list.at(i) == i);
  }
}

TEST_CASE("push back() cases") {
  // same as push_front()
}

TEST_CASE("push_back() stress test") {}

TEST_CASE("pop_front() cases") {
  // empty list pop
  // single element pop
  // multiple elements pop
}
TEST_CASE("pop_back() stress test") {}
TEST_CASE("insert() cases") {
  // empty list insert
  // insert at end
  // insert in middle
  // invalid insert
}

TEST_CASE("insert stress test") {}

TEST_CASE("remove()") {
  // remove single element
  // remove middle element
  // remove last element
  // invalid remove
}

TEST_CASE("remove() stress test") {}

TEST_CASE("contains()") {
  // valid contains
  // invalid contains
}