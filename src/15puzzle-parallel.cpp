#include <iostream>
#include <pthread.h>
#include <string>

#include "closed.h"
#include "thread.cpp"

using namespace std;

#define NUM_THREADS 4

vector<Board> initalBoards;
int numThreads;

void getPossibleBoards(Board board) {
  board.freezePriority();
  int numMovesPossible = board.numMovesPossible();
  if (board.getPossibleMoves().up) {
    Board up = Board(board);
    up.moveUp();
    up.freezePriority();
    initalBoards.push_back(up);
  }
  if (board.getPossibleMoves().down) {
    Board down = Board(board);
    down.moveDown();
    down.freezePriority();
    initalBoards.push_back(down);
  }
  if (board.getPossibleMoves().right) {
    Board right = Board(board);
    right.moveRight();
    right.freezePriority();

    initalBoards.push_back(right);
  }
  if (board.getPossibleMoves().left) {
    Board left = Board(board);
    left.moveLeft();
    left.freezePriority();
    initalBoards.push_back(left);
  }
}

void *startThread(void *threadID) {
  int tID = static_cast<int>((long)threadID);
  Board board = initalBoards.at(tID);
  Thread thread = Thread(board, tID);
  pthread_exit(NULL);
}

void *execute(void *argv) {
  string filename = string(*((char **)(argv)));
  Board blocks(filename);

  pthread_t thread[numThreads];
  getPossibleBoards(blocks);
  numThreads = blocks.numMovesPossible();

  int rc;
  for (long i = 0; i < numThreads; i++) {
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
