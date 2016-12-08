#include <algorithm>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <queue>
#include <string>
#include <utility>

#include "board.cpp"

mutex closedMutex;
mutex wonMutex;
mutex winningThreadMutex;
vector<Board> closed;
bool won = false;
int winningThread = -1;
