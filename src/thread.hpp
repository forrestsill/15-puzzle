#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Thread {
public:
  priority_queue<Board, vector<Board>, greater<vector<Board>::value_type>> open;
  int threadID;

  Thread(Board, int);
  void solve();
  void print();
};
