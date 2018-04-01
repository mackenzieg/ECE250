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
    static const double EMPTY_VAL;
    
    double **graph;
    int     *degree;

    int size;
    int edges;
    
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree(int) const;
		int edge_count() const;
		double adjacent(int, int) const;
		double distance(int, int);

    void insert(int, int, double);

    void   place_matrix(int, int, double);
    double peak_matrix(int, int);
    void   rnode_matrix(int, int);

    void destroy();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::EMPTY_VAL = std::numeric_milits<double>::infinity();

Weighted_graph::Weighted_graph(int x) :
size(x),
edges(0) {

  int h;

  if (x <= 0) {
    x = 1;
    h = 1;
  } else {
    h = (x * (x-1)) / 2;
  }

  graph = new double*[x];
  // This can be removed for efficency 
  graph[0] = 0;
  graph[1] = new double[h];

  for (int i = 2; i < x; ++i) {
    graph[i] = graph[i - 1] + i - 1;    
  }

  degree = new int[x];

  for (int i = 0; i < x; ++i) {
    degree[i] = 0;
  }
}

Weighted_graph::~Weighted_graph() {
  delete[] graph[0];
  delete[] graph;
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
  
  return peak_matrix(a, b);
}

double Weighted_graph::distance(int a, int b) {
  
}

void Weighted_graph::insert(int base, int other, double distance) {
  if (distance <= 0.0 || distance == INF 
               || base == others
               || (base >= size)
               || (other >= size)) {
    throw illegal_argument();
  }

  place_matrix(base, other, distance);
}

void Weighted_graph::place_matrix(int x, int y, double w) {
  if (x < y) {
    graph[y][x] = w;  
  } else {
    graph[x][y] = w;  
  }
}

double Weighted_graph::peak_matrix(int x, int y) {
  if (x < y) {
    return graph[y][x];  
  } else {
    return graph[x][y];  
  }
}

void Weighted_graph::rnode_matrix(int x, int y) {
  if (x < y) {
    graph[y][x] = EMPTY_VAL;  
  } else {
    graph[x][y] = EMPTY_VAL;
  }
}

void Weighted_graph::destroy() {

  int h = (size * (size - 1)) / 2;

  for (int i = 0; i < h; ++i) {
    graph[0][i] = EMPTY_VAL;
  }

  for (int i = 0; i < x; ++i) {
    degree[i] = 0;
  }

  edges = 0;
}

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
