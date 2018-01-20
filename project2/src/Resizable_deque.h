/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:

    int init_aloc;
    int allocated;
    int read_index;
    int write_index;

    Type* fifo;

    void check_resize();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque(int n)
  : init_aloc(n), allocated(n), read_index(0), write_index(0)
{
  if (n <= 0) {
    throw illegal_argument();
  }

  // Do the allocation after illegal argument check so we don't try to allocated
  // negative amount of memory. new takes a size_t which can't be unsigned
  // and won't compile but why not both

  fifo = new Type[n];
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque const &deque)
// Your initalization list
{
	// Enter your implementation here
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque(Resizable_deque &&deque)
// Your initalization list
{
	// Enter your implementation here
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
  delete[] fifo;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
  if (write_index < read_index) {
    return (write_index) + (allocated - read_index);
  }

	return write_index - read_index;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	return allocated;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	return read_index == write_index;
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
  if (empty) {
    throw underflow();
  }
	return fifo[read_index];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
  if (empty) {
    throw underflow();
  }
  // Have to subtract one to bring us to the read space end
	return fifo[write_index - 1];
}

template <typename Type>
void Resizable_deque<Type>::swap(Resizable_deque<Type> &deque) {

}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
  if (read_index == 0) {
    read_index = allocated - 1;
  } else {
    read_index -= 1;
  }

  fifo[read_index] = obj;

  check_resize(); 
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
  fifo[write_index] = obj;

  write_index = (write_index + 1) % allocated;

  check_resize();
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
  if (empty()) {
    throw underflow();
  }

  read_index = (read_index + 1) % (allocated);

  check_resize();
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
  if (empty()) {
    throw underflow();
  }

  if (write_index == 0) {
    write_index = allocated - 1;
  } else {
    write_index -= 1;
  }

  check_resize();
}

template <typename Type>
void Resizable_deque<Type>::clear() {
  if (empty()) {
    return;
  }

  allocated = init_aloc;
  delete[] fifo;
  fifo = new Type[init_aloc];

  read_index = write_index = 0;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
void Resizable_deque<Type>::check_resize() {
  if (size() > (allocated / 4) && size() < (allocated / 2)) {
    return;
  }

  int new_allocated;

  if (size() >= (allocated / 2)) {
    // Need to make array larger
    new_allocated = allocated * 2;
  } else {
    // Need to make array smaller
    new_allocated = allocated / 4;

    // If we go below the initial allocated space default back to
    // initial size
    if (new_allocated < init_aloc) {
      new_allocated = init_aloc;
    }
  }

  Type* new_fifo = new Type[new_allocated]; 

  int curr_index = read_index;

  int new_index  = 0;

  while (true) {
    if (curr_index == write_index) {
      break;
    }

    new_fifo[new_index++] = fifo[curr_index];

    
    curr_index = (curr_index + 1) % allocated;
  }

  delete[] fifo;
  fifo = new_fifo;

  allocated = new_allocated;

  read_index = 0;
  write_index = new_index;
}



/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<(std::ostream &out, Resizable_deque<T> const &list) {

  out << "[";
  for (int i = list.read_index; i != list.write_index; (i + 1) % list.allocated) {
    out << list.fifo[i] << ",";
  }

  out << std::endl;

	return out;
}

#endif
