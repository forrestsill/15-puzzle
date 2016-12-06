#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

class Solver {
public:
  Solver(Board);
  void print();

private:
  priority_queue<Board> open;
  priority_queue<Board> closed;
};

Solver::Solver(Board board) {
  open.push(board);
  int numMovesPossible = board.numMovesPossible();
  cout << "Possible moves: " << numMovesPossible
       << ". Up: " << board.getPossibleMoves().up
       << ", down: " << board.getPossibleMoves().down
       << ", left: " << board.getPossibleMoves().left
       << ", right: " << board.getPossibleMoves().right << endl;
}

void Solver::print() {
  cout << "Top of open:" << endl;
  if (open.size() > 0) {
    Board top = open.top();
    top.print();
  } else {
    cout << "Empty";
  }
  cout << endl;

  cout << "Top of close:" << endl;
  if (closed.size() > 0) {
    Board top = closed.top();
    top.print();
  } else {
    cout << "Empty";
  }
  cout << endl;
}
