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

  wonMutex.lock();
  finished = board.isSolved() || won;
  wonMutex.unlock();

  if (finished) {
    wonMutex.lock();
    won = true;
    wonMutex.unlock();
    winningThreadMutex.lock();
    if (winningThread == -1) {
      board.writeBoardToParallelFile();
      winningThread = this->threadID;
    }
    winningThreadMutex.unlock();

    return;
  }

  open.pop();
  int numMovesPossible = board.numMovesPossible();
  if (board.getPossibleMoves().up) {
    Board up = Board(board);
    up.moveUp();
    up.freezePriority();
    if (!closedContains(up)) {
      open.push(up);
    }
  }
  if (board.getPossibleMoves().down) {
    Board down = Board(board);
    down.moveDown();
    down.freezePriority();
    if (!closedContains(down)) {
      open.push(down);
    }
  }
  if (board.getPossibleMoves().right) {
    Board right = Board(board);
    right.moveRight();
    right.freezePriority();
    if (!closedContains(right)) {
      open.push(right);
    }
  }
  if (board.getPossibleMoves().left) {
    Board left = Board(board);
    left.moveLeft();
    left.freezePriority();
    if (!closedContains(left)) {
      open.push(left);
    }
  }
  closedMutex.lock();
  closed.push_back(board);
  closedMutex.unlock();
}

void Thread::print() {
  if (open.size() > 0) {
    Board top = open.top();
  }
}
