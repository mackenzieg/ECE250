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
#include <queue>
#include <list>
#include <cstring>
#include "Exception.h"

class Weighted_graph {
	private:
    static const double INF;
    
    double **graph;
    double  *dis;
    int     *deg;
    bool    *visited;

    // Determines if the distance array is dirty or not
    bool dis_dirty;

    int size;
    int edges;

    struct pair {
      int    node;
      double cost;

      bool operator<(const pair& rhs) const {
        return cost > rhs.cost;
      }
    };

    void   place_matrix(int, int, double);
    double peak_matrix(int, int);
    void   rnode_matrix(int, int);
    
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

const double Weighted_graph::INF       = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int x) :
size(x),
edges(0),
dis_dirty(true) {
  int h;

  if (x <= 0) {
    x = 1;
    h = 1;
  } else {
    h = (x * (x-1)) / 2;
  }

  graph = new double*[x];

  graph[0] = 0;
  graph[1] = new double[h];

  // Initialize all nodes to being disconnected
  for (int i = 0; i < h; ++i) {
    graph[1][i] = INF;
  }

  dis = new double[size];

  for (int i = 0; i < size; ++i) {
    dis[i] = INF;
  }

  // Fix pointers for easier use
  for (int i = 2; i < x; ++i) {
    graph[i] = graph[i - 1] + i - 1;    
  }

  deg = new int[x];

  memset(deg, 0, x);

  visited = new bool[x];
}

Weighted_graph::~Weighted_graph() {
  // Clean up all arrays
  delete[] graph[1];
  delete[] graph;
  delete[] dis;
  delete[] deg;
  delete[] visited;
}

int Weighted_graph::degree(int node) const {
  return deg[node];
}

int Weighted_graph::edge_count() const {
  return edges;
}

double Weighted_graph::adjacent(int a, int b) const {
  if (a == b) {
    return 0;
  }

  // TODO use peak_matrix just make it const
  if (a > b) {
    return graph[a][b];
  } else {
    return graph[b][a];
  }
}

double Weighted_graph::distance(int beg, int end) {
  if (beg < 0 || end < 0 || beg >= size || end >= size) {
    throw illegal_argument();
  }

  if (beg == end) {
    return 0;
  }

  // Distances were already calculated from last run
  if (!dis_dirty && dis[beg] == 0) {
    return dis[end];
  }

  std::priority_queue<pair> front_list;

  // Set distances to inf for all nodes
  for (int i = 0; i < size; ++i) {
    dis[i] = INF;
  }

  // Distance to beginning node is always 0
  dis[beg] = 0;

  // Copy zeros into memory for visited nodes
  memset(visited, 0, size);

  // Push on beginning node
  front_list.push({beg, 0.0});

  while (!front_list.empty()) {
    // Pop off min element
    pair node = front_list.top();

    front_list.pop();

    // Check if already visted.
    if (visited[node.node]) {
      continue;
    }

    // We are now visiting the node so set to true
    visited[node.node] = true;

    for (int i = 0; i < size; ++i) {
      // Check for connections. Skip over connection to itself
      if (i == node.node) {
        continue;
      }

      // Get cost of current node to its connection
      double cost = peak_matrix(node.node, i);

      // Cost will not be INF if they are connected. Could also use adjacent function
      // but don't want to waste a function call overhead
      if (cost != INF) {
        // If haven't visited the node and the new cost is lower
        if (!visited[i] && dis[node.node] + cost < dis[i]) {
          // Update lower cost
          dis[i] = dis[node.node] + cost;
          // Push on new distance to heap
          front_list.push({i, dis[i]});
        }
      }
    }
  }

  // Distances have been updated and are no longer dirty
  dis_dirty = false;

  // Return distance to node
  return dis[end];
}

void Weighted_graph::insert(int base, int other, double distance) {
  if (distance <= 0.0
               || distance == INF 
               || base == other
               || (base >= size)
               || (other >= size)
               || (base < 0)
               || (other < 0)) {
    throw illegal_argument();
  }

  // Distance matrix is dirty since new edge was inserted
  dis_dirty = true;

  // Only increase degree if we are inserting a new edge
  if (peak_matrix(base, other) == INF) {
    ++edges;
    deg[base] =  deg[base] + 1;
    deg[other] = deg[other] + 1;
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
  // Always use larger node to index matrix
  if (x < y) {
    return graph[y][x];  
  } else {
    return graph[x][y];  
  }
}

void Weighted_graph::rnode_matrix(int x, int y) {
  if (x < y) {
    graph[y][x] = INF;  
  } else {
    graph[x][y] = INF;
  }
}

void Weighted_graph::destroy() {
  // Calculate the sum of size -> 0 to get length of half matrix
  int h = (size * (size - 1)) / 2;

  // Reset all connections in half matrix
  for (int i = 0; i < h; ++i) {
    graph[1][i] = INF;
  }

  memset(deg, 0, size);

  for (int i = 0; i < size; ++i) {
    deg[i] = 0;
  }

  // Set matrix to dirty
  dis_dirty = true;
}

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
