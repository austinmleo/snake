#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "game.h"
#include "linked_list.h"
#include "node.h"

#define _WIN32_WINNT 0x0500

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(0));
	game snake = game();
	
	while (snake.gameOver == false) {
		snake.update();
		snake.draw();
	}

	Sleep(200);

	return 0;
}