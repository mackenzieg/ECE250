
#include <iostream>
#include "Double_sentinel_list.h"

void test_constructors();
void test_pop();
void test_search();

int main() {
  test_constructors();
  test_pop();
  test_search();

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
  std::cout << "Testing Pop" << std::endl;

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

}

