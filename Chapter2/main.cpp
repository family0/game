#include <iostream>
#include "Game.h"

using namespace std;

int main(int arpc, char* argv[]) {
	Game game;
	if (game.initialize()) {
		game.runLoop();
	}
	game.shutdown();
	return 0;
}