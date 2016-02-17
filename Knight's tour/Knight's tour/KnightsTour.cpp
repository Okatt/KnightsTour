/**
	KnightsTour.cpp

	@author Midas "Okatt" Buitink
	@version 0.1 14/02/16
*/

#include "Chessboard.h"
#include <iostream>

int main(){
	int size, x, y;

	// Get the user prefered board size
	std::cout << "Gimme the board size, please enter a number between 5 and 20: ";
	std::cin >> size;
	while (std::cin.fail() || size < 5 || size > 20){
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a number between 5 and 20: ";
		std::cin >> size;
	}

	// Get the user prefered starting position
	std::cout << "Gimme the start X position, please enter a number between 0 and " << size-1 << ": ";
	std::cin >> x;
	while (std::cin.fail() || x < 0 || x >= size){
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a number between 0 and " << size-1 << ": ";
		std::cin >> x;
	}

	std::cout << "Gimme the start Y position, please enter a number between 0 and " << size-1 << ": ";
	std::cin >> y;
	while (std::cin.fail() || y < 0 || y >= size){
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please enter a number between 0 and " << size-1 << ": ";
		std::cin >> y;
	}

	std::cout << std::endl;

	Chessboard b(size);
	b.solveTour(x, y);

	system("pause");
	return 0;
}