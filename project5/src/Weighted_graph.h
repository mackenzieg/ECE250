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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>

#include "Quadratic_hash_table.h"

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
    
    class Node {
      private:
        int val;
        int num_connections
        Quadratic_hash_table connections;

      public:
        Node(int val, int num_nodes);
        ~Node();

        void add_connection(int other);
        void del_connection(int other);

        int num_connections();

        bool connected(int val);

        int value();
    }

    private Node** nodes;

		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

Weighted_graph::Weighted_graph(int x) {
  if (x <= 0) {
    x = 1;
  }

  for (int i = 0; i < x; ++i) {
    nodes[i] = new Node(i, x); 
  }
}

Weighted_graph::Node::Node(int val, int num_nodes) :
  val(val), num_connections(0) {

  int power = (int) ceil(log2(num_nodes));

  connections = connections(power);
}

Weighted_graph::Node::~Node() {}

void Weighted_graph::Node::add_connection(int other) {
  ++num_connections;

  connections.insert(other);
}

void Weighted_graph::Node::del_connection(int other) {
  --num_connections;

  connections.erase(other);
}

int Weighted_graph::Node::num_connections() {
  return num_connections;
}

bool Weighted_graph::Node::connected(int val) {
  return connections.member(val);
}

int Weighted_graph::Node::connected() {
  return val;
}

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
