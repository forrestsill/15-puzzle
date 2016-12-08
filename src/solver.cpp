#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Solver {
public:
  Solver(Board);
  void solve(Board, int);
  int getMinThresholdFromNextDepth(Board);
  vector<Board> getPossibleResultingBoards(Board);
  void print();

private:
  bool solved;
  bool closedContains(Board, vector<Board>);
};

Solver::Solver(Board board) {
  if (board.isSolved()) {
    return;
  }
  int threshold = getMinThresholdFromNextDepth(board);
  cout << "Starting threshold: " << threshold << endl;
  // cout << "Starting move 1: " << endl;
  // getPossibleResultingBoards(board).at(0).print();
  // cout << "Starting move 2: " << endl;
  // getPossibleResultingBoards(board).at(1).print();
  // cout << "Starting move 3: " << endl;
  // getPossibleResultingBoards(board).at(2).print();
  while (!solved) {
    solve(board, threshold);
    threshold++;
  }

}

vector<Board> Solver::getPossibleResultingBoards(Board board) {
  moves m = board.getPossibleMoves();
  vector<Board> ret;
  if (m.up) {
    Board up = Board(board);
    up.moveUp();
    up.movesMade++;
    up.freezePriority();
    ret.push_back(up);
  }
  if (m.down) {
    Board down = Board(board);
    down.moveDown();
    down.movesMade++;
    down.freezePriority();
    ret.push_back(down);
  }
  if (m.right) {
    Board right = Board(board);
    right.moveRight();
    right.movesMade++;
    right.freezePriority();
    ret.push_back(right);
  }
  if (m.left) {
    Board left = Board(board);
    left.moveLeft();
    left.movesMade++;
    left.freezePriority();
    ret.push_back(left);
  }
  return ret;
}

int Solver::getMinThresholdFromNextDepth(Board board) {
  vector<Board> boards = getPossibleResultingBoards(board);
  int min = boards.at(0).frozenPriority;
  for (int i = 1; i < boards.size(); i++) {
    if (boards.at(i).frozenPriority < min) {
      min = boards.at(i).frozenPriority;
    }
  }
  return min;
}

void Solver::solve(Board board, int threshold) {
  vector<Board> closed;
  closed.push_back(board);
  if (board.isSolved()) {
    solved = true;
    return;
  }
  vector<Board> possibleMoves = getPossibleResultingBoards(board);
  for (int i = 0; i < possibleMoves.size(); i++) {
    Board cur = possibleMoves.at(i);

    if (cur.frozenPriority <= threshold) {
      if (!closedContains(cur, closed)) {
        cur.print();
        solve(cur, threshold);
      }
    }
  }
}

bool Solver::closedContains(Board board, vector<Board> closed) {
  for (int k = 0; k < closed.size(); k++) {
    if (board.equals(closed.at(k))) {
      return true;
    }
  }
  return false;
}

void Solver::print() {}
