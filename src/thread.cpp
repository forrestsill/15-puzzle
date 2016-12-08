#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

#include "thread.hpp"

using namespace std;

Thread::Thread(Board board, int threadID) {
  this->threadID = threadID;
  if (board.isSolved()) {
    return;
  }
  open.push(board);
  Board b = open.top();
  while (!b.isSolved() && won == 0) {
    solve();
    b = open.top();
  }
  solve();
  b.print();
  // winningThreadMutex.lock();
  cout << "Winning thread: " << winningThread << endl;
  // winningThreadMutex.unlock();

  // wonMutex.lock();
  cout << "Won: " << won << endl;
  // wonMutex.unlock();
}

bool closedContains(Board board) {
  for (int k = 0; k < closed.size(); k++) {
    if (board.equals(closed.at(k))) {
      return true;
    }
  }
  return false;
}

void Thread::solve() {
  Board board = open.top();
  board.freezePriority();

  bool finished = false;

  // wonMutex.lock();
  finished = board.isSolved() || won;
  // wonMutex.unlock();

  if (finished) {
    // cout << "FINISHED" << endl;
    wonMutex.lock();
    won = true;
    wonMutex.unlock();

    // winningThreadMutex.lock();
    winningThread = this->threadID;
    // winningThreadMutex.unlock();

    return;
  }

  open.pop();
  int numMovesPossible = board.numMovesPossible();
  cout << "Thread: " << this->threadID
       << " | Possible moves: " << numMovesPossible
       << ". Up: " << board.getPossibleMoves().up
       << ", down: " << board.getPossibleMoves().down
       << ", left: " << board.getPossibleMoves().left
       << ", right: " << board.getPossibleMoves().right << endl;
  if (board.getPossibleMoves().up) {
    Board up = Board(board);
    up.moveUp();
    cout << "UP:";
    up.freezePriority();
    up.print();
    cout << endl;
    if (!closedContains(up)) {
      open.push(up);
    }
  }
  if (board.getPossibleMoves().down) {
    Board down = Board(board);
    down.moveDown();
    cout << "DOWN:";
    down.freezePriority();
    down.print();
    cout << endl;
    if (!closedContains(down)) {
      open.push(down);
    }
  }
  if (board.getPossibleMoves().right) {
    Board right = Board(board);
    right.moveRight();
    cout << "RIGHT:";
    right.freezePriority();
    right.print();
    cout << endl;
    if (!closedContains(right)) {
      open.push(right);
    }
  }
  if (board.getPossibleMoves().left) {
    Board left = Board(board);
    left.moveLeft();
    cout << "LEFT:";
    left.freezePriority();
    left.print();
    cout << endl;
    if (!closedContains(left)) {
      open.push(left);
    }
  }
  closedMutex.lock();
  closed.push_back(board);
  closedMutex.unlock();
}

void Thread::print() {
  cout << "Top of open (size: " << open.size() << "):" << endl;
  if (open.size() > 0) {
    Board top = open.top();
    top.print();
  } else {
    cout << "Empty";
  }
  cout << endl;
}
