#include <iostream>
#include "Double_sentinel_list.h"

int main() {
	Double_sentinel_list<int> list;

	std::cout << "The list should be empty (1): " << list.empty() << std::endl;
	std::cout << "The size should be 0: " << list.size() << std::endl;

	list.push_front( 5 );
	std::cout << "The list should not be empty (0): " << list.empty() << std::endl;
	std::cout << "The size should be 1: " << list.size() << std::endl;

	std::cout << "The value of the front should be 5: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 5: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 5: " << list.back() << std::endl;

  list.erase(5);
	list.push_back( 5 );
	list.push_front( 7 );
	list.push_back( -1 );
	list.push_back( 3 );
	std::cout << list << std::endl;

	return 0;
}
