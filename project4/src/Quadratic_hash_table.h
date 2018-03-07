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

		int hash( Type const &) const;

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
    // Initialize everything to unoccupied
		occupied[i] = UNOCCUPIED;
	}
}

template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
  delete[] array;
  delete[] occupied;
}

// This function will not check to see if 
template <typename Type>
int Quadratic_hash_table<Type>::hash(const Type& obj) const {
  int hash = static_cast<int>(obj);

  if (hash < 0) {
    // If static cast gives us a negative number we need to modular and add capacity
    // to get a value within the range of the array
    hash = (hash % array_size) + capacity();
  }

  for (int i = 0; i < array_size; ++i) {
    int val = (hash + i*i) % (array_size);

    if (occupied[val] != OCCUPIED || array[val] == obj) {
      return val;
    }
  }
  
  throw overflow();
}

template <typename Type>
int Quadratic_hash_table<Type>::size() const {
  return count;
}

template <typename Type>
int Quadratic_hash_table<Type>::capacity() const {
  return array_size;
}

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const {
  return (double) (size() / capacity());
}

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const {
  return size() == 0;
}

template <typename Type>
bool Quadratic_hash_table<Type>::member(const Type& obj) const {
  // Check to see if object at hash location is occupied
  return occupied[hash(obj)] == OCCUPIED;
}

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
  return array[n];
}

template <typename Type>
void Quadratic_hash_table<Type>::insert(const Type& obj) {
  int index = hash(obj);

  // Can't use member since we need the index for later
  if (array[index] == obj) {
    return;
  }

  ++count;

  array   [index] = obj;
  occupied[index] = OCCUPIED;
}

template <typename Type>
bool Quadratic_hash_table<Type>::erase(const Type& obj) {
  if (empty()) {
    return false;
  }

  int index = hash(obj);

  // Hash didn't find valye at location
  if (array[index] != obj) {
    return false;
  }

  // Value has already been erased
  if (occupied[index] != OCCUPIED) {
    return false;
  }

  --count;

  occupied[index] = ERASED;
  return true;
}

template <typename Type>
void Quadratic_hash_table<Type>::clear() {
  count = 0;
  // Treat everything as empty
	for (int i = 0; i < array_size; ++i) {
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
