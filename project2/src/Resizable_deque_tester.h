/*************************************************
 * Resizable_deque_asArray_tester
 * A class for testing dynamic deques-as-arrays.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-8 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef DYNAMIC_DEQUE_TESTER_H
#define DYNAMIC_DEQUE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Resizable_deque.h"

#include <iostream>

template <typename Type>
class Resizable_deque_tester:public Tester< Resizable_deque<Type> > {
	using Tester< Resizable_deque<Type> >::object;
	using Tester< Resizable_deque<Type> >::command;

	public:
		Resizable_deque_tester( Resizable_deque<Type> *obj = 0 ):Tester< Resizable_deque<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For dynamic deques-as-arrays, these include:
 *
 *  Constructors
 *
 *   new             constructor     create a deque with the default array size
 *   new: n          constructor     create a deque with an array size of n
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   capacity n      capacity        the capcity equals n
 *   empty b         empty           the result is the Boolean value b
 *   front n         front           n is the first element in the deque
 *   front!          front           the underflow exception is thrown
 *   back n          back            n is the last element in the deque
 *   back!           back            the underflow exception is thrown
 *
 *  Mutators
 *
 *   push_front n    push_front      the element can be pushed (always succeeds)
 *   pop_front       pop_front       the front can be popd
 *   pop_front!      pop_front       the underflow exception is thrown
 *   push_back n     push_back       the element can be pushed (always succeeds)
 *   pop_back        pop_back        the back can be popped
 *   pop_back!       pop_back        the underflow exception is thrown
 *
 *  Others
 *
 *   assign          operator =      assign this deque to a new deque
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

template <typename Type>
void Resizable_deque_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Resizable_deque<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "new:" ) {
		int initial_capacity;

		std::cin >> initial_capacity;

		object = new Resizable_deque<Type>( initial_capacity );
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next entry read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "capacity" ) {
		// check if the capacity equals the next entry read

		int expected_capacity;

		std::cin >> expected_capacity;

		int actual_capacity = object->capacity();

		if ( actual_capacity == expected_capacity ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in capacity(): expecting the value '" << expected_capacity << "' but got '" << actual_capacity << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "front" ) {
		// checks if the first entry in the deque equals the next entry read

		Type expected_front;

		std::cin >> expected_front;

		Type actual_front = object->front();

		if ( actual_front == expected_front ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in front(): expecting the value '" << expected_front << "' but got '" << actual_front << "'" << std::endl;
		}
	} else if ( command == "front!" ) {
		// front of an empty deque - catch an exception

		Type actual_front;

		try {
			actual_front = object->front();
			std::cout << "Failure in front(): expecting to catch an exception but got '" << actual_front << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in front(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "back" ) {
		// checks if the last entry in the deque equals the next entry read

		Type expected_back;

		std::cin >> expected_back;

		Type actual_back = object->back();

		if ( actual_back == expected_back ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in back(): expecting the value '" << expected_back << "' but got '" << actual_back << "'" << std::endl;
		}
	} else if ( command == "back!" ) {
		// front of an empty deque - catch an exception

		Type actual_back;

		try {
			actual_back = object->back();
			std::cout << "Failure in back(): expecting to catch an exception but got '" << actual_back << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in back(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "push_front" ) {
		// push the next entry read to the front of the deque

		Type obj;

		std::cin >> obj;

		object->push_front( obj );
		std::cout << "Okay" << std::endl;
	} else if ( command == "pop_front" ) {
		object->pop_front();

		std::cout << "Okay" << std::endl;
	} else if ( command == "pop_front!" ) {
		// pop from an empty deque - catch an exception

		try {
			object->pop_front();
			std::cout << "Failure in pop_front(): expecting to catch an exception but did not" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in pop_front(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "push_back" ) {
		// push the next entry read to the back of the deque

		Type obj;

		std::cin >> obj;

		object->push_back( obj );
		std::cout << "Okay" << std::endl;
	} else if ( command == "pop_back" ) {
		// pop the last entry from the deque

		object->pop_back();

		std::cout << "Okay" << std::endl;
	} else if ( command == "pop_back!" ) {
		// pop from an empty deque - catch an exception

		try {
			object->pop_back();
			std::cout << "Failure in pop_back(): expecting to catch an exception but did not" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in pop_back(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear();

		std::cout << "Okay" << std::endl;
	} else if ( command == "assign" ) {
		Resizable_deque<Type> *new_object = new Resizable_deque<Type>();

		*new_object = *(object);

		std::cout << "Okay" << std::endl;

		Resizable_deque_tester<Type> tester( new_object );

		tester.run();
	} else if ( command == "move" ) {
		Resizable_deque<Type> *new_object = new Resizable_deque<Type>();

		{
			Resizable_deque<Type> cp( *object );
			*new_object = std::move( cp );
		}

		std::cout << "Okay" << std::endl;

		Resizable_deque_tester<Type> tester( new_object );

		tester.run();
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif