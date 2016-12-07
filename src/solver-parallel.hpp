#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Solver {
public:
  Solver(Board);
  bool closedContains(Board);
  void printClosed();
  void print();
};
