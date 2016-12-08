#include <iostream>
#include <pthread.h>
#include <string>

#include "closed.h"
#include "thread.cpp"

using namespace std;

#define NUM_THREADS 2

vector<Board> initalBoards;

void getPossibleBoards(Board board) {
  board.freezePriority();
  int numMovesPossible = board.numMovesPossible();
  cout << "Possible moves: " << numMovesPossible
       << ". Up: " << board.getPossibleMoves().up
       << ", down: " << board.getPossibleMoves().down
       << ", left: " << board.getPossibleMoves().left
       << ", right: " << board.getPossibleMoves().right << endl;
  if (board.getPossibleMoves().up) {
    Board up = Board(board);
    up.moveUp();
    // cout << "UP:";
    up.freezePriority();
    // up.print();
    // cout << endl;
    initalBoards.push_back(up);
  }
  if (board.getPossibleMoves().down) {
    Board down = Board(board);
    down.moveDown();
    // cout << "DOWN:";
    down.freezePriority();
    // down.print();
    // cout << endl;
    initalBoards.push_back(down);
  }
  if (board.getPossibleMoves().right) {
    Board right = Board(board);
    right.moveRight();
    // cout << "RIGHT:";
    right.freezePriority();
    // right.print();
    // cout << endl;

    initalBoards.push_back(right);
  }
  if (board.getPossibleMoves().left) {
    Board left = Board(board);
    left.moveLeft();
    // cout << "LEFT:";
    left.freezePriority();
    // left.print();
    // cout << endl;
    initalBoards.push_back(left);
  }
  // for (int i = 0; i < initalBoards.size(); i++) {
  //   initalBoards.at(i).print();
  // }
}

void *startThread(void *threadID) {
  cout << "Successfully created thread : " << (long)threadID << endl;
  int tID = static_cast<int>((long)threadID);
  Board board = initalBoards.at(tID);
  board.print();
  Thread thread = Thread(board, tID);
  // cout << "Winning thread: " << winningThread << endl;
  pthread_exit(NULL);
}

void *execute(void *argv) {
  string filename = string(*((char **)(argv)));
  Board blocks(filename);

  // initalBoards = Solver solver(blocks);
  // solver.print();

  pthread_t thread[NUM_THREADS];
  getPossibleBoards(blocks);

  int rc;
  for (long i = 0; i < NUM_THREADS; i++) {
    cout << "Creating thread: " << i << endl;
    rc = pthread_create(&thread[i], NULL, startThread, (void *)i);

    if (rc) {
      cout << "Error creating thread:" << i << endl;
      exit(-1);
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  pthread_t thread;
  int rc;

  rc = pthread_create(&thread, NULL, execute, (void *)&filename);

  if (rc) {
    cout << "Error creating starting thread." << endl;
    exit(-1);
  }

  pthread_exit(NULL);
}
