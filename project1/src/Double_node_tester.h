/*************************************************
 * Double_node_tester<Type>
 * A class for testing nodes used in doubly linked lists.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-2010 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef DOUBLE_NODE_TESTER_H
#define DOUBLE_NODE_TESTER_H

#include "Exception.h"
#include "Tester.h"
#include "Double_sentinel_list.h"

#include <iostream>

template <typename Type>
class Double_node_tester : public Tester<typename Double_sentinel_list<Type>::Double_node> {
	using Tester< typename Double_sentinel_list<Type>::Double_node >::object;
	using Tester< typename Double_sentinel_list<Type>::Double_node >::command;

	public:
		Double_node_tester( typename Double_sentinel_list<Type>::Double_node *obj = nullptr );
		void process();
};

template <typename Type>
Double_node_tester<Type>::Double_node_tester( typename Double_sentinel_list<Type>::Double_node *obj ):
Tester< typename Double_sentinel_list<Type>::Double_node >( obj ) {
	// empty
}

/****************************************************
 * void process()
 *
 * Process the current command.  For double nodes, these include:
 *
 *                 Member
 *   Flag         Function         Tests if ...
 *
 *  Accessors
 *
 *   next          next()          the next pointer can be followed
 *   next0         next()          the next pointer is 'nullptr'
 *   previous      previous()      the previous pointer can be followed
 *   previous0     previous()      the previous pointer is 'nullptr'
 *   value n       value()         the stored value is n
 ****************************************************/

template <typename Type>
void Double_node_tester<Type>::process() {
	if ( command == "next" ) {
		typename Double_sentinel_list<Type>::Double_node *actual_next = Double_node_tester<Type>::object->next();

		if ( actual_next != nullptr ) {
			object = actual_next;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in next(): expecting to follow a non-null next pointer" << std::endl;
		}
	} else if ( command == "next0" ) {
		if ( object->next() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in next(): expecting a null (nullptr) next pointer" << std::endl;
		}
	} else if ( command == "value" ) {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = object->value();

		if ( expected_value == actual_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in value(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	} else if ( command == "previous" ) {
		typename Double_sentinel_list<Type>::Double_node *actual_previous = Double_node_tester<Type>::object->previous();

		if ( actual_previous != nullptr ) {
			object = actual_previous;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in previous(): expecting to follow a non-null previous pointer" << std::endl;
		}
	} else if ( command == "previous0" ) {
		if ( object->previous() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in previous(): expecting a null (nullptr) previous pointer" << std::endl;
		}
	} else if ( command == "value" ) {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = object->value();

		if ( expected_value == actual_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in value(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}

#endif
