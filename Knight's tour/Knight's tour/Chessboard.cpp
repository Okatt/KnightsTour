/**
Chessboard.h

@author Midas "Okatt" Buitink
@version 0.1 14/02/16
*/

#include "Chessboard.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// The knight's move set
const int Chessboard::possibleMoves[][8] = { { 1,  2,  2,  1, -1, -2, -2, -1 },
											 { 2,  1, -1, -2, -2, -1,  1,  2 } };

// Constructor
Chessboard::Chessboard()
{	
	this->N = 5;
	this->M = this->N*this->N - 1;

	// Allocate memory for the chessboard
	this->data = new int*[this->N];
	for (int i = 0; i < this->N; i++){
		this->data[i] = new int[this->N];
	}

	// Initialize the chessboard
	for (int x = 0; x < this->N; x++) {
		for (int y = 0; y < this->N; y++) {
			this->data[x][y] = -1;
		}
	}
}

// Constructor
Chessboard::Chessboard(int size)
{
	this->N = size;
	this->M = this->N*this->N - 1;

	// Allocate memory for the chessboard
	this->data = new int*[this->N];
	for (int i = 0; i < size; i++){
		this->data[i] = new int[this->N];
	}

	// Initialize the chessboard
	for (int x = 0; x < this->N; x++) {
		for (int y = 0; y < this->N; y++) {
			this->data[x][y] = -1;
		}
	}
}

// Deconstructor
Chessboard::~Chessboard()
{	
	// Free the memory
	for (int i = 0; i < this->N; ++i) {
		delete[] this->data[i];
	}
	delete[] this->data;
}

// Solves the knight's tour from start position (x, y)
void Chessboard::solveTour(int x, int y)
{
	// If N is uneven and the knight's starting position is on a "black" space, there is no solution path
	if (this->N % 2 != 0 || x + y != 0 || (x + y) % 2 != 0){
		std::cout << "No solution was found..." << std::endl;
		return;
	}
	
	// Find and print the solution
	if (this->makeMove(x, y, 0)){
		std::cout << "Solution found!" << std::endl;
		this->printSolution();
	}else{
		std::cout << "No solution was found..." << std::endl;
	}
}

// Recursively find a solution, returns false if no solution was found
bool Chessboard::makeMove(int x, int y, int m)
{
	// Return false if this space is out of bounds
	if (!this->isSafe(x, y)) { return false; }

	// Return false if this space has already been visited
	if (this->data[x][y] != -1) { return false; }

	// Mark the current space as visited (by assigning the value of the current step)
	this->data[x][y] = m;

	// Returns true if the solution has been found
	if (m == this->M){ return true; }
	else {
		bool result = false;
			
		// Create a vector that contains all possible moves, sorted according to Warndorff's rule
		std::vector<std::pair<int, int>> sorted;
		sorted = this->sortMoves(x, y);

		// Loop through all possible moves (most of the time only the first move is checked)
		for (std::vector<std::pair<int, int>>::const_iterator it = sorted.begin(); it != sorted.end(); ++it){
			int nx = x + possibleMoves[0][it->first];
			int ny = y + possibleMoves[1][it->first];
			result = result || this->makeMove(nx, ny, m + 1);
		}

		if (result){ return true; }
		else{ this->data[x][y] = -1; return false; }
	}
}

// Returns a vector with all possible moves sorted from least next moves to most next moves
std::vector<std::pair<int, int>> Chessboard::sortMoves(int x, int y)
{
	// Create a vector of all possible moves, add heuristics according to Warnsdorff's rule
	std::vector<std::pair<int, int>> sorted;
	for (int i = 0; i < 8; i++){
		int nx = x + possibleMoves[0][i];
		int ny = y + possibleMoves[1][i];
		if (this->isSafe(nx, ny) && this->data[nx][ny]){
			sorted.push_back(std::make_pair(i, this->nextMoves(nx, ny)));
		}
	}

	// Sort the vector according to Warnsdorff's rule
	std::sort(sorted.begin(), sorted.end(), [](const std::pair<int, int> &left, const std::pair<int, int> &right) {
		return left.second < right.second;
	});

	return sorted;
}

// Returns the amount of possible moves from space (x, y)
int Chessboard::nextMoves(int x, int y)
{
	int nm = 0;
	for (int i = 0; i < 8; i++){
		int nx = x + possibleMoves[0][i];
		int ny = y + possibleMoves[1][i];
		if (this->isSafe(nx, ny) && this->data[nx][ny] == -1) { nm++; }
	}
	return nm;
}

// Return true if the coordinates are on the chessboar
bool Chessboard::isSafe(int x, int y)
{
	return (x >= 0 && x < this->N && y >= 0 && y < this->N);
}

// Prints the solution
void Chessboard::printSolution(){
	std::cout << this->toString() << std::endl;
}

// Returns the chessboard as a string
std::string Chessboard::toString()
{
	std::string s = "\n";

	for (int y = 0; y < this->N; y++) {
		for (int x = 0; x < this->N; x++) {
			if (data[x][y] < 10){ s += "0"; }
			if (data[x][y] < 100 && this->M >= 100){ s += "0"; }
			s += std::to_string(data[x][y]) + " ";
		}
		// Clean vertical spacing
		if (this->N != 20){ s += "\n\n"; }
		else{ s += "\n"; }
	}
	return s;
}