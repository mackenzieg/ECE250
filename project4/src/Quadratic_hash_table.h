/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  mj2goodw @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		bin_state_t *occupied;

		int hash( Type const &, int& val) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();

		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
  delete[] array;
  delete[] occupied;
}

/*
 * Returns vals:
 *      -2: object already inside array
 *      -1: array is full
 *       0: hash was successful
 */
template <typename Type>
int Quadratic_hash_table<Type>::hash(const Type$ obj, int& val) const {
  int hash = static_cast<int>(obj);
  for (int i = 0; i < table_size; ++i) {
    val = (hash + i*i) % (table_size - 1);

    if (array[val] == obj) {
      return -2;
    }

    if (occupied[val] != OCCUPIED) {
      return 0;
    }
  }

  return -1;
}

template <typename Type>
int Quadratic_hash_table<Type>::size() {
  return count;
}

template <typename Type>
int Quadratic_hash_table<Type>::capacity() {
  return array_size;
}

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() {
  return (double) (size() / capacity());
}

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const {
  return size() == 0;
}

template <typename Type>
bool Quadratic_hash_table<Type>::member(const Type& obj) const {
  return occupied[hash(obj)] == OCCUPIED;
}

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
  return array[n];
}

template <typename Type>
void Quadratic_hash_table<Type>::insert(const Type& obj) {
  int index = hash(obj);

  // Object is already inside the table
  if (index == -2) {
    return;
  }

  // No more space is left in the table
  if (index == -1) {
    throw overflow();
  }

  array   [index] = obj;
  occupied[index] = OCCUPIED;
}

template <typename Type>
bool Quadratic_hash_table<Type>::erase(const Type& obj) {
  int index = hash(obj);

  // Object was not found in array
  if (index == -1) {

  }
}

template <typename Type>
void Quadratic_hash_table<Type>::clear() :
  count(0) {
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

// Your implementation here

template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
