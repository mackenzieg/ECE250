/*****************************************
 * UW User ID: mj2goodw 
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
        Double_node();
				Double_node(Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr);

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list(Double_sentinel_list const &);
		Double_sentinel_list(Double_sentinel_list &&);
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap(Double_sentinel_list &);
		Double_sentinel_list &operator=(Double_sentinel_list);
		Double_sentinel_list &operator=(Double_sentinel_list &&);

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase(Type const &);

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

    // Will delete a node and relink the remaining nodes
    // WARNING: does not check to see if the node you give it is a sentinel
    // if you give this function a sentinel you will possibly receive a seg fault
    void erase_link(Double_node* node);

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Double_sentinel_list<T> const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

// Initialize list_head and list_tail sentinels
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() :
                     list_head(new Double_node(Type(), nullptr, nullptr)),
                     list_tail(new Double_node(Type(), nullptr, nullptr)),
                     list_size(0) {
  // Link sentinels together
  list_head->next_node     = list_tail;
  list_tail->previous_node = list_head;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const &list) :
                     Double_sentinel_list() {
  Double_node* current_node = list.rbegin();

  // While current_node doesn't equal the tail sentinel
  while (current_node != list.end()) {
    // This should call the copy constructor on the value
    push_back(current_node->value());
    // Update current node to next node in chain
    current_node = current_node->next();
  }
}

// Since we are just moving we can do a shallow copy
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> &&list) :
                                                 Double_sentinel_list() {
  // Set list size to zero so that it doesn't try to access its data. Just to be safe
  // also update the sentinels to point to each other
  swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
  // Another solution is to start at the head sentinel and go until a nullptr
  // but I already made this erase_link function so might as well use it.
  // Is destructor performance really important on the first project anyway???
  while (!empty()) {
    erase_link(rbegin());
  }

  delete list_head;
  delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
  // Could either check to see if list_size is zero or if list_head->next == list_tail 
	return list_size == 0;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
  if (empty()) {
    throw underflow();
  }

	return rbegin()->value();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
  if (empty()) {
    throw underflow();
  }

	return rend()->value();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return list_tail->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find(Type const &obj) const {
  Double_node* current = rbegin();
  // Loop over objects until we hit the end sentinel
  while (current != end()) {
    if (current->value() == obj) {
      return current;
    }
    current = current->next();
  }
	return nullptr;
}

template <typename Type>
int Double_sentinel_list<Type>::count(Type const &obj) const {
  int num = 0;
  Double_node* current = rbegin();
  // Same logic as find basically
  while (current != end()) {
    if (current->value() == obj) {
      ++num;
    }
    current = current->next();
  }
	return num;
}

template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list) {
	std::swap(list_head, list.list_head);
	std::swap(list_tail, list.list_tail);
	std::swap(list_size, list.list_size);
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> rhs) {
	swap(rhs);

	return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> &&rhs) {
	swap(rhs);

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front(Type const &obj) {
  // This should work even if list is empty as previous_head will be the tail sentinel
  // TODO rename these to something better such as previous_rbegin
  Double_node* previous_head = rbegin();
  Double_node* new_node      = new Double_node(obj, list_head, previous_head);

  // Update pointers to new node
  begin()->next_node           = new_node;
  previous_head->previous_node = new_node;

  ++list_size;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back(Type const &obj) {
  // Same logic as push_front just reversed
  Double_node* previous_tail = rend();
  Double_node* new_node      = new Double_node(obj, previous_tail, list_tail);

  end()->previous_node     = new_node;
  previous_tail->next_node = new_node;

  ++list_size;
}

// If list is empty this function will do nothing
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
  if (empty()) {
    return;
  }

  // Update the node infront of the node we are removing and update its previous pointer
  // to point to the head
  Double_node* new_head = rbegin()->next_node;
  new_head->previous_node = list_head;

  delete list_head->next();
  list_head->next_node = new_head;
}

// If list is empty this function will do nothing
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
  if (empty()) {
    return;
  }

  // Same logic as pop_front just reversed
  Double_node* new_tail = rend()->previous();
  new_tail->next_node = list_tail;

  delete list_tail->previous();
  list_tail->previous_node = new_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::erase(Type const &obj) {
  int num_del = 0;
  // Create two since we have to delete the nodes we are removing.
  // Next is basically a temp variable so we can delete without losing the current
  // objects next pointer
  Double_node* current = rbegin();
  Double_node* next    = current;
  while (current != list_tail) {
    next = current->next();
    if (current->value() == obj) {
      erase_link(current);
      ++num_del;
    }

    current = next;
  }
	return num_del;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(Type const &nv, Double_sentinel_list<Type>::Double_node *pn,
                                                                     Double_sentinel_list<Type>::Double_node *nn) :
                                                                     node_value(nv),
                                                                     previous_node(pn),
                                                                     next_node(nn) {}


template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
void Double_sentinel_list<Type>::erase_link(Double_node* node) {
  // Relink the remnaining links back together
  node->previous()->next_node = node->next();
  node->next()->previous_node = node->previous();
  --list_size;
  delete node;
}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<(std::ostream &out, Double_sentinel_list<T> const &list) {
  out << "head->";

	for (typename Double_sentinel_list<T>::Double_node *ptr = list.rbegin(); ptr != list.end(); ptr = ptr->next()) {
    out << ptr->value() << "->";
  }

	out << "tail";

	return out;
}

#endif
