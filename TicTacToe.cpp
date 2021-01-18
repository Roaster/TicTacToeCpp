// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>

//implement number guessing game to see who goes first.

struct game {

	void start();
	//display board
	void displayBoard();
	//keep track of whose turn
	//check to see if move is valid
	bool validMove(int);
	// player 1 = 0   player 2 = 1
	int turn = 0;
	//keep track of winner
	//keep track of board
	std::vector<char> board;
	void isWinner();
	bool gameover = false;
};

void game::displayBoard() {
	std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |" << std::endl;
	std::cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |" << std::endl;
	std::cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |" << std::endl;
}

bool game::validMove(int position) {
	if (board.at(position) != 'X' || board.at(position) != 'O') {
		return true;
	} 
	if(turn == 0) std::cout << "Invalid move." << std::endl;
	return false;
}

void game::isWinner() {
	if (
		//Horizontal winners
		board[0] == board[1] && board[0] == board[2] && board[0] != ' ' ||
		board[3] == board[4] && board[3] == board[5] && board[3] != ' ' ||
		board[6] == board[7] && board[6] == board[8] && board[6] != ' ' || 
		//diagonals
		board[0] == board[5] && board[0] == board[8] && board[0] != ' ' || 
		board[2] == board[4] && board[2] == board[6] && board[2] != ' ' || 
		//verticals
		board[0] == board[3] && board[0] == board[6] && board[0] != ' ' ||
		board[1] == board[4] && board[1] == board[7] && board[1] != ' ' || 
		board[2] == board[5] && board[2] == board[8] && board[2] != ' '  ) {


		gameover = true;
		if (turn == 0) {
			std::cout << "You lose!";
		}
		else {
			std::cout << "You win!";
		}
		
	}

}

void game::start() {
	std::cout << "Starting game....\n";

	//Initialize first 9 spaces of vector to empty
	char counter = '0';
	for (int i = 0; i < 9; ++i) {
		board.push_back(counter);
		++counter;
	}
	displayBoard();
	return;
}

int main()
{
	game x;

	x.start();
	while (!x.gameover) {
		int nextMove;
		
		std::cout << std::endl;
		//players turn
		if (x.turn == 0) {
			std::cout << "Your turn! ";
			//capture the move
			std::cin >> nextMove;
			if (nextMove > 9 || nextMove < 0) {
				std::cout << "Please enter a position greater than 0 and less than 9!" << std::endl;
				std::cin >> nextMove;
			}

			//check to see if its valid
			if (x.validMove(nextMove)) {
				while (!x.validMove(nextMove)) {
					std::cin >> nextMove;
				}
				x.board.at(nextMove) = 'X';
				//x.displayBoard();
				x.turn = 1;
			}
		}
		else {
			std::cout << "Computers turn!" << std::endl;
			//random number holder
			int random;

			//generate a random into modulo 9
			random = rand() % 9;
			if (!x.validMove(random)) {
				random = rand() % 9;
				while (!x.validMove(random)) {
					random = rand() % 9;
				}
			}
			x.board.at(random) = 'O';
			x.turn = 0;
		}

		//clear console screen for better appearance.
		if (!x.gameover) std::cout << "\033[2J\033[1;1H";

		x.displayBoard();
		x.isWinner();
		
		
	}
	return 0;
}

