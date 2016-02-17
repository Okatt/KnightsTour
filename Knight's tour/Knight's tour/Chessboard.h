/**
	Chessboard.h

	@author Midas "Okatt" Buitink
	@version 0.1 14/02/16
*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <vector>

class Chessboard
{
	private:
		int N;									// The board size
		int M;									// The last move
		int** data;								// The board data
		static const int possibleMoves[][8];	// The knight's move set

		std::vector<std::pair<int, int>> sortMoves(int, int);
		int nextMoves(int, int);
		bool makeMove(int, int, int);
		bool isSafe(int, int);
		void printSolution();

	public:
		Chessboard();
		Chessboard(int);
		~Chessboard();

		void solveTour(int, int);
		std::string toString();
};

#endif // CHESSBOARD_H

