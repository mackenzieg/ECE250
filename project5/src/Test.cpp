#include "Weighted_graph.h"
#include <iostream>

using namespace std;

int main() {
  Weighted_graph graph(10);

  graph.insert(0, 9, 14);

  graph.insert(0, 1, 10);
  graph.insert(1, 9, 5);

  cout << graph.distance(0, 9) << endl;
}
