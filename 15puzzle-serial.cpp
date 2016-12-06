#include <iostream>
#include <string>

#include "board.cpp"
#include "solver.cpp"

using namespace std;

int main (int argc, const char* argv[]) {
	Board blocks (argv[1]);
	int returnCode = 0;
	blocks.print();
	return returnCode;
}