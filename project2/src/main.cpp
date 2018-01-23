#include <iostream>
#include "Resizable_deque.h"

using namespace std;

int main() {

  Resizable_deque<int> que(6);

  que.push_front(1);
  que.push_front(1);
  que.push_front(2);
  que.push_front(1);
  que.push_front(1);

  Resizable_deque<int> another(std::move(que));

  cout << que << endl;
  cout << another << endl;

}

