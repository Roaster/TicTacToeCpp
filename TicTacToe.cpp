// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>

//implement number guessing game to see who goes first.
void clearConsole() {
	std::cout << "\033[2J\033[1;1H";
}

struct game {

	void start();
	//display menu
	void displayMenu();
	//display board
	void displayBoard();
	//check to see if move is valid

	void computerTurn();
	bool validMove(int);
	// player 1 = 0   player 2 = 1
	int turn = 0;
	//board
	std::vector<char> board;
	//check for winner
	void isWinner();
	bool gameover = false;

	int playerWins = 0;
	int aiWins = 0;
};

void game::displayBoard() {
	std::cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |" << std::endl;
	std::cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |" << std::endl;
	std::cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |" << std::endl;
}

void game::displayMenu() {
	std::cout << "Welcome to TicTacToe!" << std::endl;
	std::cout << "1. Quick match" << std::endl;
	std::cout << "2. Records" << std::endl;
	std::cout << "3. Quit" << std::endl;
	
	int selection;

	std::cin >> selection;

	switch (selection)
	{
	case 1: 
		clearConsole();
		start();
		return;
	case 2:
		clearConsole();
		std::cout << "Player has won " << playerWins << " rounds." << std::endl;
		std::cout << "Ai has won " << aiWins << " rounds." << std::endl;
		break;
	case 3: 
		gameover = true;
	default:
		break;
	}

}

bool game::validMove(int position) {
	if (board.at(position) != 'X' && board.at(position) != 'O') {
		return true;
	} 
	//only display invalid move option for user
	if(turn == 0) std::cout << "Invalid move." << std::endl;
	return false;
}

void game::computerTurn() {
	for (int i = 0; i < board.size(); ++i ) {
		if (board[i] == 'O') {
			if (i != 0 && validMove((i - 1) % 9)) {
				board.at((i - 1) % 9) = 'O';
				turn = 0;
				return;
			}
			else if (validMove((i + 1) % 9)) {
				board.at((i + 1) % 9) = 'O';
				turn = 0;
				return;
			}
			else if (validMove((i + 3) % 9)) {
				board.at((i + 3) % 9) = 'O';
				turn = 0;
				return;
			}
		}
	}

	int random = rand() % 9;
	if (!validMove(random)) {
		random = rand() % 9;
		while (!validMove(random)) {
			random = rand() % 9;
		}
	}
	board.at(random) = 'O';
	turn = 0;

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


		//gameover = true;
		if (turn == 0) {
			std::cout << "You lose!" << std::endl;
			++aiWins;
			turn = 1;
		}
		else {
			std::cout << "You win!" << std::endl;
			++playerWins;
			turn = 0;
		}

		std::cout << "Play Again? y/n" << std::endl;
		char answer;
		std:: cin >> answer;
		if (answer == 'y') {
			clearConsole();
			board.clear();
			start();
		}
		else {
			clearConsole();
			displayMenu();
		}

		return;
	}

}

void game::start() {
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

	x.displayMenu();
	//if (!x.gameover) std::cout << "\033[2J\033[1;1H";

	//x.start();
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

			x.computerTurn();
			//generate a random into modulo 9
			
		}

		//clear console screen for better appearance.
		if (!x.gameover) std::cout << "\033[2J\033[1;1H";

		x.displayBoard();
		x.isWinner();
		
		
	}
	return 0;
}

