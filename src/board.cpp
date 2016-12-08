#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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
  int frozenPriority;

  Board(string);
  int hamming();
  int manhattan();
  int priority();

  bool equals(Board);
  bool isSolved();
  int numMovesPossible();
  Point getBlankSpace();
  moves getPossibleMoves();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void freezePriority();
  void writeBoardToSerialFile();
  void writeBoardToParallelFile();
  string toString();
  void print();

private:
  int numBlocksInWrongPosition();
  void printInfo();
};

void Board::moveUp() {
  Point blank = getBlankSpace();
  blocks[blank.x][blank.y] = blocks[blank.x - 1][blank.y];
  blocks[blank.x - 1][blank.y] = 0;
  movesMade++;
}

void Board::moveDown() {
  Point blank = getBlankSpace();
  blocks[blank.x][blank.y] = blocks[blank.x + 1][blank.y];
  blocks[blank.x + 1][blank.y] = 0;
  movesMade++;
}

void Board::moveLeft() {
  Point blank = getBlankSpace();
  blocks[blank.x][blank.y] = blocks[blank.x][blank.y - 1];
  blocks[blank.x][blank.y - 1] = 0;
  movesMade++;
}

void Board::moveRight() {
  Point blank = getBlankSpace();
  blocks[blank.x][blank.y] = blocks[blank.x][blank.y + 1];
  blocks[blank.x][blank.y + 1] = 0;
  movesMade++;
}

void Board::freezePriority() { this->frozenPriority = priority(); }

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

int Board::hamming() { return numBlocksInWrongPosition(); }

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

bool Board::equals(Board b) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (this->blocks[i][j] != b.blocks[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void Board::print() {
  cout << toString();
  printInfo();
}

string Board::toString() {
  ostringstream os;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      string toPrint = to_string(this->blocks[i][j]);
      if (!toPrint.compare("0")) {
        toPrint = "-";
      }
      os << toPrint << "\t";
    }
    os << "\n";
  }
  string str = os.str();
  return str;
}

void Board::writeBoardToSerialFile() {
  ofstream file;
  file.open("output-serial.txt");
  file << toString();
  file.close();
}

void Board::writeBoardToParallelFile() {
  ofstream file;
  file.open("output-parallel.txt");
  file << toString();
  file.close();
}

void Board::printInfo() {
  cout << "Solved?: " << isSolved() << ", Hamming: " << hamming()
       << ", Manhattan: " << manhattan()
       << ", frozenPriority: " << this->frozenPriority << "\n";
}

bool operator>(const Board &lhs, const Board &rhs) {
  return lhs.frozenPriority > rhs.frozenPriority;
}
