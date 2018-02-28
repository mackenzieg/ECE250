#include "Quadratic_hash_table.h"
#include <iostream>

using namespace std;

int main() {
  Quadratic_hash_table<int> table(5);

  table.insert(31);

  cout << "Bin 0: " << table.bin(0) << endl;

  cout << table.erase(31) << endl;
  cout << table.erase(31) << endl;
}
