
#include <iostream>
#include "Double_sentinel_list.h"

void test_constructors();

int main() {
  test_constructors();

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
