#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Point {
public:
  int x;
  int y;
  Point(int, int);
  int numMovesPossible();
};

Point::Point(int x, int y) {
  this->x = x;
  this->y = y;
}

int Point::numMovesPossible() {
  if (this->x == 0 || this->x == 3) {
    if (this->y == 0 || this->y == 3) {
      return 2;
    }
    return 3;
  }
  if (this->y == 0 || this->y == 3) {
    return 3;
  }
  return 4;
}

struct moves {
  bool up;
  bool down;
  bool left;
  bool right;
};

class Board {
public:
  int blocks[4][4];
  int movesMade;
  Board(string);
  int hamming();
  int manhattan();
  int priority();
  void print();
  bool isSolved();
  int numMovesPossible();
  Point getBlankSpace();
  moves getPossibleMoves();

private:
  int numBlocksInWrongPosition();
  void printInfo();
};

int Board::numBlocksInWrongPosition() {
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!(i == 3 && j == 3) && this->blocks[i][j] != i * 4 + j + 1) {
        count++;
      }
    }
  }
  return count;
}

int Board::hamming() { return numBlocksInWrongPosition() + this->movesMade; }

moves Board::getPossibleMoves() {
  Point p = getBlankSpace();
  moves m;
  m.up = true;
  m.down = true;
  m.left = true;
  m.right = true;

  if (p.y == 0) {
    m.left = false;
  }
  if (p.y == 3) {
    m.right = false;
  }
  if (p.x == 0) {
    m.up = false;
  }
  if (p.x == 3) {
    m.down = false;
  }

  return m;
}
int getDistance(int x, int y, int goal) {
  return abs((x % 4) - ((goal - 1) % 4)) + abs(((goal - 1) / 4) - y);
}

int Board::manhattan() {
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!(i == 3 && j == 3)) {
        count += getDistance(j, i, blocks[i][j]);
      }
    }
  }
  return count;
}

int Board::priority() { return hamming() + manhattan(); }

Point Board::getBlankSpace() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (blocks[i][j] == 0) {
        Point p(i, j);
        return p;
      }
    }
  }
  throw 1;
}

int Board::numMovesPossible() { return getBlankSpace().numMovesPossible(); }

Board::Board(string filename) {
  ifstream file(filename.c_str());
  string a;
  for (int i = 0; i < 16; i++) {
    file >> a;
    if (!a.compare("-")) {
      a = "0";
    }
    this->blocks[i / 4][i % 4] = stoi(a);
  }
  this->movesMade = 0;
}

bool Board::isSolved() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      if (blocks[i][j] != j + 1 + (i * 4)) {
        if (blocks[i][j] == 0 && i == 3 && j == 3) {
          return true;
        }
        return false;
      }
  }
  return true;
}

void Board::print() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      string toPrint = to_string(this->blocks[i][j]);
      if (!toPrint.compare("0")) {
        toPrint = "-";
      }
      cout << toPrint << "\t";
    }
    cout << "\n";
  }
  printInfo();
}

void Board::printInfo() {
  cout << "Solved?: " << isSolved() << ", Hamming: " << hamming()
       << ", Manhattan: " << manhattan() << "\n";
  // cout << "X: " << x+1 << ", Y: " << y+1 << ", Block: " << goal << ",
  // X-Distance: " << abs((x % 4) - ((goal - 1) % 4)) << ", Y-Distance: " <<
  // abs(((goal - 1) / 4) - y) << "\n";
}

bool operator<(Board lhs, Board rhs) { return lhs.priority() < rhs.priority(); }
