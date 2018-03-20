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
#include "Exception.h"

class Weighted_graph {
	private:
    static const double INFINITY;
    
    double **graph;
    int     *degree;

    int size;
    int edges;
    
		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree(int) const;
		int edge_count() const;
		double adjacent(int, int) const;
		double distance(int, int);

		void insert(int, int, double);

    void destroy();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INFINITY = std::numeric_milits<double>::infinity();

Weighted_graph::Weighted_graph(int x) :
size(x),
edges(0) {

  if (x <= 0) {
    throw illegal_argument();
  }

  for (int i = 0; i < x; ++i) {
    graph[i] = new double[x];
  }

  for (int m = 0; m < x; ++m) {
    for (int n = 0; n < x; ++n) {
      graph[m][n] = INFINITY;
    }
  }

  degree = new int[x];

  for (int i = 0; i < x; ++i) {
    degree[i] = 0;
  }
}

Weighted_graph::~Weighted_graph() {
  for (int i = 0; i < size; ++i) {
    delete[] graph[i];
  }

  delete[] degree;
}

int Weighted_graph::degree(int node) const {
  return degree[node];
}

int Weighted_graph::edge_count() const {
  return edges;
}

double Weighted_graph::adjacent(int a, int b) const {
  if (a == b) {
    return 0;
  }

  return graph[a][b];
}

double Weighted_graph::distance(int a, int b) {

}

void Weighted_graph::insert(int base, int other, double distance) {

}

void Weighted_graph::destroy() {
  for (int m = 0; m < x; ++m) {
    for (int n = 0; n < x; ++n) {
      graph[m][n] = INFINITY;
    }
  }

  for (int i = 0; i < x; ++i) {
    degree[i] = 0;
  }

  edges = 0;
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
