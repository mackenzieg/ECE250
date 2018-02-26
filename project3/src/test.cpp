#include <iostream>
#include "Search_tree.h"

int main() {
	Search_tree<int> tree;

	for ( int i = 1; i <= 30; ++i ) {
		std::cout << tree.insert( (83*i) % 30 );
	}

	std::cout << std::endl;

	for ( int i = 1; i <= 30; ++i ) {
		std::cout << tree.insert( (97*i) % 30 );
	}

	std::cout << std::endl;

	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	tree.clear();

	std::cout << "--> ";
	

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;
	
	
	std::cout << "Custome tests start here" << std::endl;
	for ( int i = 1; i <= 30; ++i ) {
		std::cout << tree.insert( (83*i) % 30 );
	}

	std::cout << std::endl;

	for ( int i = 1; i <= 10; ++i ) {
		std::cout << tree.erase(i*2);
	}
	
	
	for ( int i = 20; i <= 29; ++i ) {
		std::cout << tree.erase(i*2);
	}
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;
	std::cout << std::endl;
	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}


	std::cout << std::endl;

	tree.clear();
    std::cout << "Cleared" <<std::endl;
	std::cout << "--> ";
	

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	for ( int i = 1; i <= 30; ++i ) {
		std::cout << tree.insert( i );
	}
	std::cout << std::endl;

	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;
	tree.clear();
	std::cout << "Cleared" <<std::endl;
	
	for ( int i = 32; i >=0; --i ) {
		std::cout << tree.insert( i );
	}
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;
	tree.clear();
	std::cout << "Cleared" <<std::endl;
	
	std::cout << tree.insert( 1 );
	std::cout << tree.insert( 0 );
	std::cout << tree.insert( 5 );
	std::cout << tree.insert( 7 );
	std::cout << tree.insert( 4 );
	std::cout << tree.insert( 3 );
	std::cout << std::endl;
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}
	
	std::cout << std::endl;
	tree.clear();
	std::cout << "Cleared" <<std::endl;
	
	std::cout << tree.insert( 10 );
	std::cout << tree.insert( 11 );
	std::cout << tree.insert( 5 );
	std::cout << tree.insert( 7 );
	std::cout << tree.insert( 4 );
	std::cout << tree.insert( 9 );
	std::cout << tree.insert( 12 );
	std::cout << std::endl;
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	
	std::cout << tree.erase(11);
	std::cout << tree.erase(4);
	std::cout << std::endl;
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	
	tree.clear();
	std::cout << "Cleared" <<std::endl;
	
	std::cout << tree.insert( 10 );
	std::cout << tree.insert( 11 );
	std::cout << tree.insert( 5 );
	std::cout << tree.insert( 7 );
	std::cout << tree.insert( 4 );
	std::cout << std::endl;
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	
	std::cout << tree.erase(11);
	std::cout << tree.erase(4);
	std::cout << std::endl;
	
	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	
	
	
	return 0;
}
