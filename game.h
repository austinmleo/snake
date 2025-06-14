#pragma once

#include <vector>
#include <string>
#include <random>
#include <iostream>

#include "linked_list.h"

struct linked_list;

class game 
{
private:
	int size, score, direction, goal;
	linked_list snake;

public:
	bool gameOver = false;
	bool start = false;

	game(int size = 25, int score = 4);

	bool outOfBounds(int loc);
	void fillBoard(std::string& board);
	void update();
	void draw();
	int getSize() { return size; };
};
