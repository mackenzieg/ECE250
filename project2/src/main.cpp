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
  cout << que << endl;
  que.pop_front();
  cout << que << endl;
  que.pop_front();
  cout << que << endl;
  que.pop_front();
  cout << que << endl;
  que.pop_front();

  cout << que << endl;
  que.pop_front();

  cout << que << endl;

  Resizable_deque<int> another(std::move(que));


}

