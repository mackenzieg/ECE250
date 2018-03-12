#include "Quadratic_hash_table.h"
#include <iostream>

using namespace std;

int main() {
  Quadratic_hash_table<int> table(-11);

  table.insert(-120);

  cout << table << endl;

  cout << table.load_factor() << endl;

  Quadratic_hash_table<int> another_table(table);

  cout << another_table << endl;

  table.erase(-120);

  cout << table.load_factor() << endl;
}
