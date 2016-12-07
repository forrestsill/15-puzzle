#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>

#include "solver-parallel.hpp"
#include "thread.cpp"

using namespace std;

Solver::Solver(Board board) {
  if (board.isSolved()) {
    return;
  }

  // Thread initialThread = Thread(board, 0, threads[0]);

  // open.push(board);
  // Board b = open.top();
  // while (!b.isSolved()) {
  //   solve();
  //   b = open.top();
  // }
  // solve();
  // b.writeBoardToParallelFile();
}

void Solver::printClosed() {
  cout << "List of closed:" << endl;
  for (int k = 0; k < closed->size(); k++) {
    closed->at(k).print();
  }
}

void Solver::print() {
  // cout << "Top of open (size: " << open.size() << "):" << endl;
  // if (open.size() > 0) {
  //   Board top = open.top();
  //   top.print();
  // } else {
  //   cout << "Empty";
  // }
  // cout << endl;

  cout << "Closed (size: " << closed->size() << "):" << endl;
  if (closed->size() == 0) {
    cout << "Empty" << endl;
  } else {
    printClosed();
  }
}

bool Solver::closedContains(Board board) {
  for (int k = 0; k < closed->size(); k++) {
    if (board.equals(closed->at(k))) {
      return true;
    }
  }
  return false;
}
