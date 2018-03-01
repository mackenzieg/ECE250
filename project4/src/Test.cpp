#include "Quadratic_hash_table.h"
#include <iostream>

using namespace std;

int main() {
  Quadratic_hash_table<int> table(5);

  table.insert(31);

  cout << "Bin 31: " << table.bin(31) << endl;

  cout << table << endl;

  cout << table.erase(31) << endl;
  cout << table.erase(31) << endl;
}
