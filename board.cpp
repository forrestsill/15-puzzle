#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Board {
	public:
		int blocks[4][4];
		int movesMade;
		Board (string);
		int hamming();
		int manhattan();
		void print();

	private:
		int numBlocksInWrongPosition();
		void printHM();
};

int Board::numBlocksInWrongPosition() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!(i == 3 && j == 3) && this->blocks[i][j] != i*4 + j + 1) { count++; }
		}
	}
	return count;
}

int Board::hamming() {
	return numBlocksInWrongPosition() + this->movesMade;
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

Board::Board(string filename) {
	ifstream file(filename.c_str());
	int a;
	for (int i = 0; i < 15; i++) {
		file >> a;
		this->blocks[i/4][i%4] = a;
	}
	this->movesMade = 0;
}

void Board::print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			string toPrint = to_string(this->blocks[i][j]);
			if (!toPrint.compare("0")) { toPrint = "-"; }
			cout << toPrint << "\t";
		}
		cout << "\n";
	}
	cout << "Hamming: " << hamming() << ", Manhattan: " << manhattan() << "\n";
}

void Board::printHM() {
	cout << "Hamming: " << hamming() << ", Manhattan: " << manhattan() << "\n";
	// cout << "X: " << x+1 << ", Y: " << y+1 << ", Block: " << goal << ", X-Distance: " << abs((x % 4) - ((goal - 1) % 4)) << ", Y-Distance: " << abs(((goal - 1) / 4) - y) << "\n";
}