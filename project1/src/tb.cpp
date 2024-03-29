
#include <iostream>
#include "Double_sentinel_list.h"
#include "Exception.h"

void test_constructors();
void test_pop();
void test_search();
void test_frontback();

int main() {
  test_constructors();
  test_pop();
  test_search();
  test_frontback();

	return 0;
}

// This assumes that insertion works
void test_constructors() {
  std::cout << "Testing constructors" << std::endl;

  // Test copy constructor
  {
    Double_sentinel_list<int> list;

    for (int i = 0; i < 10; ++i) {
      list.push_front(i);
    }

    std::cout << "Before copy: " << list << std::endl;

    Double_sentinel_list<int> second_list(list);

    std::cout << "Copied list: " << second_list << std::endl;
  }

  {
    Double_sentinel_list<int> list;

    for (int i = 10; i < 20; ++i) {
      list.push_front(i);
    }

    std::cout << "Before move: " << list << std::endl;

    Double_sentinel_list<int> second_list(std::move(list));

    std::cout << "Moved list: " << second_list << std::endl;
  }
}

void test_pop() {
  std::cout << "Testing pop" << std::endl;

  {
    Double_sentinel_list<int> list;
    for (int i = 0; i < 10; ++i) {
      list.push_front(i);
    }

    std::cout << "Before pop_back: " << list << std::endl;

    list.pop_back();

    std::cout << "After  pop_back: " << list << std::endl;
  }

  {
    Double_sentinel_list<int> list;
    for (int i = 0; i < 10; ++i) {
      list.push_front(i);
    }

    std::cout << "Before pop_front: " << list << std::endl;

    list.pop_front();

    std::cout << "After  pop_front: " << list << std::endl;
  }

  {
    Double_sentinel_list<int> list;

    std::cout << "Before pop on empty: " << list << std::endl;

    for (int i = 0; i < 10; ++i) {
      list.pop_front();
    }

    std::cout << "After pop on empty: " << list << std::endl;
  }
}

void test_search() {
  std::cout << "Testing search" << std::endl;

  {
    Double_sentinel_list<int> list;

    std::cout << "Found nothing in empty list (1): " << (list.find(5) == nullptr) << std::endl;
    std::cout << "Count in empty list (0): " << list.count(5) << std::endl;

    list.push_front(5);

    std::cout << list << std::endl;

    std::cout << "Found correct node with single element (1): " << (list.find(5)->previous() == list.rend()) << std::endl;
    std::cout << "Count in list with one element (1): " << list.count(5) << std::endl;

    list.push_front(5);


    std::cout << list << std::endl;

    std::cout << "Found correct node with multiple elements (1): " << (list.find(5)->previous() == list.rend()) << std::endl;
    std::cout << "Count in list with multiple elements (2): " << list.count(5) << std::endl;

    std::cout << "Count of objects not in list (0): " << list.count(-1) << std::endl;
  }
}

void test_frontback() {
  std::cout << "Testing front/back" << std::endl;

  {
    Double_sentinel_list<int> list;

    bool caught = false;
    try {
      list.front();
    } catch (underflow& e) {
      caught = true;
    }

    std::cout << "Caught front exception (1): " << caught << std::endl;

    caught = false;

    try {
      list.back();
    } catch (underflow& e) {
      caught = true;
    }

    std::cout << "Caught back exception (1): " << caught << std::endl;

    list.push_front(6);
    list.push_back(9);

    caught = false;

    try {
      list.back();
    } catch (underflow& e) {
      caught = true;
    }

    std::cout << "Caught back exception (0): " << caught << std::endl;

    caught = false;

    try {
      list.back();
    } catch (underflow& e) {
      caught = true;
    }

    std::cout << "Caught back exception (0): " << caught << std::endl;

    std::cout << "Front value (6): " << list.front() << std::endl;
    std::cout << "Back  value (9): " << list.back() << std::endl;
  }
}

