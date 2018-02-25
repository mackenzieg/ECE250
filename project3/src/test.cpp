#include <iostream>
#include "Search_tree.h"

using namespace std;

int main() {
	Search_tree<int> tree;

  std::cout << "Starting" << std::endl;

  std::cout << tree << std::endl;

  tree.insert(10);
  tree.insert(20);
  tree.insert(5);
  tree.insert(2);
  tree.insert(6);

  cout << tree << endl;

  tree.erase(10);

  cout << tree << endl;

	// for ( int i = 1; i <= 30; ++i ) {
  //   tree.insert(((83 * i) % 30));
	// }


	// std::cout << "Front:   " << tree.front()   << std::endl;
	// std::cout << "Back:    " << tree.back()    << std::endl;
	// std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	// std::cout << "--> ";

	// for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
	// 	std::cout << *itr << " ";
	// }

	// std::cout << std::endl;

	// std::cout << "--> ";

	// for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
	// 	std::cout << *itr << " ";
	// }

	// std::cout << std::endl;

  // std::cout << tree << std::endl;

  // tree.erase(16);

  // std::cout << tree << std::endl;

	return 0;
}
