#include <iostream>
#include <string>

#include "board.cpp"
#include "solver.cpp"

using namespace std;

int main (int argc, const char* argv[]) {
	string filename = argv[1];
	Board blocks (filename);
	int returnCode = 0;
	blocks.print();
	return returnCode;
}
