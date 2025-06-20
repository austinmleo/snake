#include "game.h"
#include "node.h"
#include <Windows.h>
#include <stdlib.h>

// Create game board of size x size with a starting length of score.
game::game(int size, int score) {
	this->size = size;
	this->score = score;
	direction = rand() % 4;

	snake = linked_list();

	int pos;

	do {
		pos = rand() % (size * (size + 1));
	} while (outOfBounds(pos));
	snake.insert(pos);

	do {
		goal = rand() % (size * (size + 1));
	} while (outOfBounds(goal) || snake.contains(goal));
}

// Checks if loc is out of bounds
bool game::outOfBounds(int loc) {
	if (loc <= 0 || loc > (size * (size + 1)) || loc % (size + 1) == 0) {
		return true;
	}

	return false;
}


void game::update() {
	if (this->start == false) {
		if (GetAsyncKeyState(' ') & 0x0001) {
			this->start = true;
		}
		return;
	}

	if (GetAsyncKeyState('A') & 0x0001) {
		if (direction != 2) {
			direction = 0;
		}
	} 
	else if (GetAsyncKeyState('S') & 0x0001) {
		if (direction != 3) {
			direction = 1;
		}
	}
	else if (GetAsyncKeyState('D') & 0x0001) {
		if (direction != 0) {
			direction = 2;
		}
	}
	else if (GetAsyncKeyState('W') & 0x0001) {
		if (direction != 1) {
			direction = 3;
		}
	}

	int next;
	int head = snake.head->value;

	switch (direction) {
		case 0:
			next = head - 1;
			break;
		case 1:
			next = head + (size + 1);
			break;
		case 2:
			next = head + 1;
			break;
		default:
			next = head - (size + 1);
			break;
	}

	if (snake.contains(next) || outOfBounds(next)) {
		gameOver = true;
	} 
	else {
		snake.insert(next);

		if (next == goal) {
			score++;

			do {
				goal = rand() % (size * (size + 1));
			} while (outOfBounds(goal) || snake.contains(goal));
		}

		if (score < snake.length) {
			snake.remove();
		}
	}
}

//
void game::fillBoard(std::string& board) {
	node* temp = snake.head;

	while (temp != nullptr) {
		std::string s = std::string(1,char(219));

		if (temp == snake.head) {
			switch (direction) {
			case 0:
				s = "<";
				break;
			case 1:
				s = "v";
				break;
			case 2:
				s = ">";
				break;
			default:
				s = "^";
				break;
			}
		}

		board.replace(temp->value, 1, s);
		temp = temp->next;
	}

	board.replace(goal, 1, std::string(1,char(177)));
}

void game::draw() {
	int padding = 2;
	std::string board = std::string(size * (size + 1), ' ');

	fillBoard(board);

	std::cout << "\033[0;0H" << std::string(padding, ' ') << char(201) << std::string(size, char(205)) << char(187) << "\n";

	for (int i = 0; i < size; i++) {
		std::string row = std::string(padding, ' ') + char(186) + board.substr(i * (size + 1) + 1, size) +char(186) + "\n";
		std::cout << row;
	}

	std::string s = "SCORE: " + std::to_string(score);

	std::cout << std::string(padding, ' ') << char(204) << std::string(size, char(205)) << char(185) << "\n";
	std::cout << std::string(padding, ' ') << char(186) << std::string((size - s.length()) / 2, ' ') << s << std::string((size - s.length() + 1) / 2, ' ') << char(186) << "\n";
	std::cout << std::string(padding, ' ') << char(200) << std::string(size, char(205)) << char(188) << "\033[s";
	

	if (this->start == false) {
		std::string r = "-USE A S D & W TO MOVE-";
		std::string begin = "-PRESS SPACE TO BEGIN-";
		std::cout << "\033[" << std::to_string(int(size / 2)) << ";0H" << std::string(padding, ' ') << char(186) << std::string((size - r.length()) / 2, ' ') << r;
		std::cout << "\033[" << std::to_string(int(size / 2 + 1)) << ";0H" << std::string(padding, ' ') << char(186) << std::string((size - begin.length()) / 2, ' ') << begin << "\033[u";
	
	} 
	else if (this->gameOver == true) {
		std::string end = "-GAME OVER-";
		std::cout << "\033[" << std::to_string(int(size / 2 + 1))  << ";0H" << std::string(padding, ' ') << char(186) << std::string((size - end.length()) / 2, ' ') << end << "\033[u";
	}

	Sleep(100);
}