#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Solver {
public:
  Solver(Board);
  void solve();
  void printClosed();
  void print();

private:
  priority_queue<Board, vector<Board>, greater<vector<Board>::value_type>> open;
  vector<Board> closed;

  bool closedContains(Board);
};

Solver::Solver(Board board) {
  if (board.isSolved()) {
    return;
  }
  open.push(board);
  Board b = open.top();
  while (!b.isSolved()) {
    solve();
    b = open.top();
  }
  solve();
  b.writeBoardToSerialFile();
}

void Solver::solve() {
  Board board = open.top();
  board.freezePriority();
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
  closed.push_back(board);
}

void Solver::printClosed() {
}

void Solver::print() {
  if (open.size() > 0) {
    Board top = open.top();
  } else {
    cout << "Empty";
  }

  if (closed.size() == 0) {
    cout << "Empty" << endl;
  } else {
  }
}

bool Solver::closedContains(Board board) {
  for (int k = 0; k < closed.size(); k++) {
    if (board.equals(closed.at(k))) {
      return true;
    }
  }
  return false;
}
