/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2018
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type() );

				void update_height();

				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );

        void print( std::ostream &out, int tabs = 0);
		};


		Node *root_node;
		int tree_size;

		// Hint as to how to start your linked list of the nodes in order 
		Node *front_sentinel;
		Node *back_sentinel;

	public:
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;

			// Make the search tree a friend so that it can call the constructor
			friend class Search_tree;
		};

		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Search_tree();
		~Search_tree();

		bool empty() const;
		int size() const;
		int height() const;

		Type front() const;
		Type back() const;

		Iterator begin();
		Iterator end();
		Iterator rbegin();
		Iterator rend();
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return ( root_node == nullptr );
}

template <typename Type>
void Search_tree<Type>::Node::print( std::ostream &out, int tabs ) {
	for(int i = 0; i < tabs; i++){
		out << " ";
	}
	out << (tabs ? "`==" : "");
	if(this == nullptr){
		out << "xx";
		out << " h=-1" << std::endl;
	} else {
		out << node_value;
		out << " h=" << height() << std::endl;
		left_tree->print(out, tabs+1);
		right_tree->print(out, tabs+1);
	}
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj );

    front_sentinel->next_node = root_node;
    root_node->previous_node = front_sentinel;

    root_node->next_node = back_sentinel;
    back_sentinel->previous_node = root_node;

		tree_size = 1;

		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		++tree_size;
		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		--tree_size;
		return true;
	} else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {
	// does nothing
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return ( right_tree == nullptr ) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
      // Create new left tree node for obj
			left_tree = new Search_tree<Type>::Node( obj );

      // Save previous node for linking
      Node* prev_prev = to_this->previous_node;

      // link previous next mode to new tree
      prev_prev->next_node = left_tree;
      // link tree back to previous node
      left_tree->previous_node = prev_prev;

      // link tree to next node
      left_tree->next_node = to_this;
      // link next node back to tree
      to_this->previous_node = left_tree;

      left_tree->update_height();

			update_height();

			return true;
		} else {
			if ( left_tree->insert( obj, left_tree ) ) {
        // Imbalance on left side
        if ((right_tree == nullptr) || (left_tree->height() - right_tree->height() == 2)) {
          Node* f = this;
          Node* b = this->left_tree;
          // left-left balance
          if (left_tree->left_tree->height() > left_tree->right_tree->height()) {
            to_this = b;
            Node* old_right = b->right_tree;
            // Logic to rotate nodes
            b->right_tree = f;
            f->left_tree  = old_right;

            // Update heights after
            f->update_height();
            b->update_height();

          // left-right balance
          } else {
            Node* d = b->right_tree;

            Node* dr = d->right_tree;
            Node* dl = d->left_tree;

            d->left_tree = b;
            d->right_tree = f;

            b->right_tree = dl;
            f->left_tree  = dr;

            to_this = d;

            // Update heights after
            f->update_height();
            b->update_height();
            d->update_height();
          }
        }

				update_height();
				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {

			right_tree = new Search_tree<Type>::Node( obj );

      Node* next_next = to_this->next_node;

      to_this->next_node = right_tree;
      right_tree->previous_node = to_this;

      right_tree->next_node = next_next;
      next_next->previous_node = right_tree;

			update_height();

			return true;
		} else {
			if ( right_tree->insert( obj, right_tree ) ) {
        if ((left_tree == nullptr) || (right_tree->height() - left_tree->height() == 2)) {
          Node* f = this;
          Node* b = this->right_tree;
          // right-right 
          if (right_tree->right_tree->height() > right_tree->left_tree->height()) {
            to_this = b;
            Node* old_left = b->left_tree;
            b->left_tree = f;
            f->right_tree  = old_left;

            f->update_height();
            b->update_height();

          // right-left
          } else {
            Node* d = b->left_tree;

            Node* dr = d->left_tree;
            Node* dl = d->right_tree;

            d->right_tree = b;
            d->left_tree = f;

            b->left_tree = dl;
            f->right_tree  = dr;

            to_this = d;

            f->update_height();
            b->update_height();
            d->update_height();
          }
        }

				update_height();

				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
        
        if ((left_tree == nullptr) || (right_tree->height() - left_tree->height() == 2)) {
          Node* f = this;
          Node* b = this->right_tree;
          // right-right 
          if (right_tree->right_tree->height() > right_tree->left_tree->height()) {
            to_this = b;
            Node* old_left = b->left_tree;
            b->left_tree = f;
            f->right_tree  = old_left;

            f->update_height();
            b->update_height();

          // right-left
          } else {
            Node* d = b->left_tree;

            Node* dr = d->left_tree;
            Node* dl = d->right_tree;

            d->right_tree = b;
            d->left_tree = f;

            b->left_tree = dl;
            f->right_tree  = dr;

            to_this = d;

            f->update_height();
            b->update_height();
            d->update_height();
          }
        }

				update_height();
				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
        if ((right_tree == nullptr) || (left_tree->height() - right_tree->height() == 2)) {
          Node* f = this;
          Node* b = this->left_tree;
          // left-left
          if (left_tree->left_tree->height() > left_tree->right_tree->height()) {
            to_this = b;
            Node* old_right = b->right_tree;
            b->right_tree = f;
            f->left_tree  = old_right;

            f->update_height();
            b->update_height();

          // left-right
          } else {
            Node* d = b->right_tree;

            Node* dr = d->right_tree;
            Node* dl = d->left_tree;

            d->left_tree = b;
            d->right_tree = f;

            b->right_tree = dl;
            f->left_tree  = dr;

            to_this = d;

            f->update_height();
            b->update_height();
            d->update_height();
          }
        }

				update_height();
				return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );


		if ( is_leaf() ) {

			to_this = nullptr;

      previous_node->next_node = next_node;
      next_node->previous_node = previous_node;
			delete this;
		} else if ( left_tree == nullptr ) {
			to_this = right_tree;
      to_this->update_height();

      previous_node->next_node = next_node;
      next_node->previous_node = previous_node;
			delete this;
		} else if ( right_tree == nullptr ) {
			to_this = left_tree;
      to_this->update_height();

      previous_node->next_node = next_node;
      next_node->previous_node = previous_node;
			delete this;
		} else {
			node_value = right_tree->front()->node_value;
			right_tree->erase( node_value, right_tree );
			update_height();

      if ((right_tree == nullptr) || (left_tree->height() - right_tree->height() == 2)) {
        Node* f = this;
        Node* b = this->left_tree;
        // left-left
        if (left_tree->left_tree->height() > left_tree->right_tree->height()) {
          to_this = b;
          Node* old_right = b->right_tree;
          b->right_tree = f;
          f->left_tree  = old_right;

          f->update_height();
          b->update_height();

        // left-right
        } else {
          Node* d = b->right_tree;

          Node* dr = d->right_tree;
          Node* dl = d->left_tree;

          d->left_tree = b;
          d->right_tree = f;

          b->right_tree = dl;
          f->left_tree  = dr;

          to_this = d;

          f->update_height();
          b->update_height();
          d->update_height();
        }
      } else if ((left_tree == nullptr) || (right_tree->height() - left_tree->height() == 2)) {
          Node* f = this;
          Node* b = this->right_tree;
          // right-right 
          if (right_tree->right_tree->height() > right_tree->left_tree->height()) {
            to_this = b;
            Node* old_left = b->left_tree;
            b->left_tree = f;
            f->right_tree  = old_left;

            f->update_height();
            b->update_height();

          // right-left
          } else {
            Node* d = b->left_tree;

            Node* dr = d->left_tree;
            Node* dl = d->right_tree;

            d->right_tree = b;
            d->left_tree = f;

            b->left_tree = dl;
            f->right_tree  = dr;

            to_this = d;

            f->update_height();
            b->update_height();
            d->update_height();
          }
        }
		}

		return true;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
  if (current_node->next_node != nullptr) {
    current_node = current_node->next_node;
  }
	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
  if (current_node->previous_node != nullptr) {
    current_node = current_node->previous_node;
  }
	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	list.root_node->print(out);

	return out;
}

#endif
